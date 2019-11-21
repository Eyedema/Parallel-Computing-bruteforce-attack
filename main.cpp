#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "PCWorker.h"
#include "CSVWriter.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Too few arguments. Here's how to use the program:" << std::endl;
        std::cout << "PC_project.exe password_1 [password_2 ... password_n] numberOfTries" << std::endl;
        return 1;
    }
    std::vector<int> numberOfThreads = {1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 24, 100, 150};
    CSVWriter CSVWriter;
    for (int i = 1; i <= argc-2; ++i) {
        PCWorker PCWorker(argv[i], std::atoi(argv[argc-1]));
        PCWorker.sequentialAttack();
        for (int &number: numberOfThreads) {
            PCWorker.parallelAttack(number);
            PCWorker.parallelAutomaticAttack(number);
            PCWorker.computeSpeedUp();
            std::vector<std::pair<std::string, std::vector<long>>> values = {{"Run Times Sequential",
                                                                                     PCWorker.getRunTimesSequential()},
                                                                             {"Run Times Parallel",
                                                                                     PCWorker.getRunTimesParallel()},
                                                                             {"Run Times Automatic Parallel",
                                                                                     PCWorker.getRunTimesAutomaticParallel()}};

            std::vector<std::pair<std::string, std::vector<double>>> valuesDouble = {{"Speed up from Sequential to Parallel",
                                                                                             PCWorker.getSpeedUpSequentialToParallel()},
                                                                                     {"Speed up from Sequential to Automatic Parallel",
                                                                                             PCWorker.getSpeedUpSequentialToAutomaticParallel()}};

            CSVWriter.writeCSV(std::string("./results/PC Results ")+argv[1]+" "+std::to_string(number)+".csv", values, valuesDouble, std::strtol(argv[2], nullptr, 0));
            PCWorker.reset();
        }
    }

    return 0;
}