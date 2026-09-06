#ifndef HARQ_PROCESS_H
#define HARQ_PROCESS_H

#include "channel.h"

struct PacketResult {
    bool success;
    int attempts;
};

class HARQProcess {
public:
    HARQProcess(int maxRetransmissions, bool softCombining);

    PacketResult transmitPacket(
        Channel& channel,
        double snrDb,
        double configuredBler
    );

private:
    int maxRetransmissions;
    bool softCombining;
};

#endif