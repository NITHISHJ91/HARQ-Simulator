#include "channel.h"

#include <algorithm>
#include <cmath>

Channel::Channel(unsigned int seed)
    : generator(seed),
      uniform(0.0, 1.0),
      rayleighPower(1.0) {
}

bool Channel::isPacketError(double errorProbability) {
    return uniform(generator) < clampProbability(errorProbability);
}

double Channel::fadingPower() {
    return std::max(1e-9, rayleighPower(generator));
}

double Channel::clampProbability(double value) {
    return std::max(1e-6, std::min(0.999999, value));
}

double Channel::snrToBLER(double snrDb) {
    const double midpoint = 5.0;
    const double slope = 1.25;

    double bler =
        1.0 / (1.0 + std::exp((snrDb - midpoint) / slope));

    return clampProbability(bler);
}