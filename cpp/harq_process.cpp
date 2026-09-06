#include "harq_process.h"

#include <cmath>

HARQProcess::HARQProcess(
    int maxRetransmissions,
    bool softCombining
)
    : maxRetransmissions(maxRetransmissions),
      softCombining(softCombining) {
}

PacketResult HARQProcess::transmitPacket(
    Channel& channel,
    double snrDb,
    double configuredBler
) {
    const int maxAttempts = maxRetransmissions + 1;

    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {

        double fadingDb =
            10.0 * std::log10(channel.fadingPower());

        double instantaneousSnr =
            snrDb + fadingDb;

        double combinedSnr =
            instantaneousSnr;

        /*
         * Chase Combining:
         * each retransmission adds received signal energy.
         */
        if (softCombining) {
            combinedSnr +=
                10.0 * std::log10(
                    static_cast<double>(attempt)
                );
        }

        double baselineBler =
            Channel::snrToBLER(snrDb);

        double channelBler =
            Channel::snrToBLER(combinedSnr);

        double adjustedBler =
            configuredBler *
            (channelBler / baselineBler);

        adjustedBler =
            Channel::clampProbability(
                adjustedBler
            );

        if (!channel.isPacketError(adjustedBler)) {
            return {true, attempt};
        }
    }

    return {false, maxAttempts};
}