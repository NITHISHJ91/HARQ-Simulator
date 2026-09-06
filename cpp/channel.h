#ifndef CHANNEL_H
#define CHANNEL_H

#include <random>

class Channel {
public:
    explicit Channel(unsigned int seed = 42);

    bool isPacketError(double errorProbability);

    double fadingPower();

    static double clampProbability(double value);

    static double snrToBLER(double snrDb);

private:
    std::mt19937 generator;
    std::uniform_real_distribution<double> uniform;
    std::exponential_distribution<double> rayleighPower;
};

#endif