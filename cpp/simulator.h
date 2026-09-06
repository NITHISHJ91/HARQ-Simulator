#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <string>

class Simulator {
public:
    Simulator(
        int packets = 10000,
        int maxRetransmissions = 3,
        int payloadBits = 12000
    );

    void run(const std::string& outputFile);

private:
    int packets;
    int maxRetransmissions;
    int payloadBits;

    void runSNRSweep(std::ofstream& output);

    void runBLERSweep(std::ofstream& output);

    void runProcessSweep(std::ofstream& output);

    void simulatePoint(
        std::ofstream& output,
        const std::string& experiment,
        double snrDb,
        double bler,
        int numProcesses,
        bool softCombining,
        unsigned int seed
    );
};

#endif