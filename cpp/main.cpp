#include "simulator.h"

#include <filesystem>
#include <iostream>

int main() {

    try {

        std::filesystem::create_directories(
            "results/figures"
        );

        Simulator simulator(
            10000,
            3,
            12000
        );

        simulator.run(
            "results/harq_results.csv"
        );

        std::cout
            << "HARQ simulation completed successfully."
            << std::endl;

        std::cout
            << "Results: results/harq_results.csv"
            << std::endl;

        return 0;
    }

    catch (const std::exception& error) {

        std::cerr
            << "Simulation error: "
            << error.what()
            << std::endl;

        return 1;
    }
}