#include "simulator.h"

#include "channel.h"
#include "harq_process.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

Simulator::Simulator(
    int packets,
    int maxRetransmissions,
    int payloadBits
)
    : packets(packets),
      maxRetransmissions(maxRetransmissions),
      payloadBits(payloadBits) {
}

void Simulator::run(
    const std::string& outputFile
) {
    std::ofstream output(outputFile);

    if (!output) {
        throw std::runtime_error(
            "Could not open output file: " +
            outputFile
        );
    }

    output
        << "experiment,"
        << "snr_db,"
        << "bler,"
        << "num_processes,"
        << "soft_combining,"
        << "throughput_mbps,"
        << "average_latency_slots,"
        << "success_rate,"
        << "retransmission_rate\n";

    runSNRSweep(output);
    runBLERSweep(output);
    runProcessSweep(output);
}

void Simulator::simulatePoint(
    std::ofstream& output,
    const std::string& experiment,
    double snrDb,
    double bler,
    int numProcesses,
    bool softCombining,
    unsigned int seed
) {
    Channel channel(seed);

    HARQProcess harq(
        maxRetransmissions,
        softCombining
    );

    long long successfulPackets = 0;
    long long totalAttempts = 0;
    long long totalLatencySlots = 0;

    for (int i = 0; i < packets; ++i) {

        PacketResult result =
            harq.transmitPacket(
                channel,
                snrDb,
                bler
            );

        totalAttempts += result.attempts;

        totalLatencySlots +=
            result.attempts;

        if (result.success) {
            ++successfulPackets;
        }
    }

    /*
     * N-process stop-and-wait abstraction.
     * More parallel HARQ processes allow the pipeline
     * to hide waiting time.
     */
    double pipelineSlots =
        static_cast<double>(totalAttempts) /
        std::max(1, numProcesses);

    double throughputMbps =
        (successfulPackets * payloadBits) /
        std::max(1.0, pipelineSlots) /
        1e6;

    double successRate =
        static_cast<double>(successfulPackets) /
        packets;

    double retransmissionRate =
        static_cast<double>(
            totalAttempts - packets
        ) /
        static_cast<double>(packets);

    double averageLatency =
        static_cast<double>(
            totalLatencySlots
        ) /
        packets;

    output
        << experiment << ","
        << std::fixed
        << std::setprecision(2)
        << snrDb << ","

        << std::setprecision(4)
        << bler << ","

        << numProcesses << ","

        << (softCombining ? 1 : 0) << ","

        << std::setprecision(6)
        << throughputMbps << ","

        << std::setprecision(4)
        << averageLatency << ","

        << successRate << ","

        << retransmissionRate
        << "\n";
}

void Simulator::runSNRSweep(
    std::ofstream& output
) {
    const double snrs[] = {
        -2.0,
        2.0,
        6.0,
        10.0,
        14.0
    };

    for (double snr : snrs) {

        double bler =
            Channel::snrToBLER(snr);

        for (bool soft : {false, true}) {

            simulatePoint(
                output,
                "snr_sweep",
                snr,
                bler,
                4,
                soft,
                static_cast<unsigned int>(
                    1000 +
                    static_cast<int>(snr * 10) +
                    soft
                )
            );
        }
    }
}

void Simulator::runBLERSweep(
    std::ofstream& output
) {
    const double blers[] = {
        0.05,
        0.15,
        0.30,
        0.50,
        0.70
    };

    for (double bler : blers) {

        for (bool soft : {false, true}) {

            simulatePoint(
                output,
                "bler_sweep",
                5.0,
                bler,
                4,
                soft,
                static_cast<unsigned int>(
                    2000 +
                    static_cast<int>(
                        bler * 1000
                    ) +
                    soft
                )
            );
        }
    }
}

void Simulator::runProcessSweep(
    std::ofstream& output
) {
    const int processCounts[] = {
        1,
        2,
        4,
        8,
        16
    };

    const double snr = 6.0;

    const double bler =
        Channel::snrToBLER(snr);

    for (int processes : processCounts) {

        for (bool soft : {false, true}) {

            simulatePoint(
                output,
                "process_sweep",
                snr,
                bler,
                processes,
                soft,
                static_cast<unsigned int>(
                    3000 +
                    processes * 10 +
                    soft
                )
            );
        }
    }
}