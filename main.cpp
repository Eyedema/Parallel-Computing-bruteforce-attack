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
    std::vector<int> numberOfThreads = {2, 4, 6, 8, 10, 12, 14, 16, 20, 100, 500, 1000};
    std::vector<std::string> columnNames = {"Run Times Sequential", "Run Times Parallel",
                                            "Run Times Automatic Parallel", "Speed up from Sequential to Parallel",
                                            "Speed up from Sequential to Automatic Parallel", "Tries", "Thread",
                                            "Password"};
    CSVWriter CSVWriter("PC Results.csv", columnNames);
    for (int i = 1; i <= argc - 2; ++i) {
        PCWorker PCWorker(argv[i], std::atoi(argv[argc - 1]));
        PCWorker.sequentialAttack();
        for (int &number: numberOfThreads) {
            PCWorker.parallelAttack(number);
            PCWorker.parallelAutomaticAttack(number);
            PCWorker.computeSpeedUp();
            std::vector<std::vector<long>> values = {
                    PCWorker.getRunTimesSequential(),
                    PCWorker.getRunTimesParallel(),
                    PCWorker.getRunTimesAutomaticParallel()};

            std::vector<std::vector<double>> valuesDouble = {
                    PCWorker.getSpeedUpSequentialToParallel(),
                    PCWorker.getSpeedUpSequentialToAutomaticParallel()};
            CSVWriter.writeCSV(values, valuesDouble, std::stoi(argv[argc - 1]), argv[i], number);
            PCWorker.reset();
        }
    }
    return 0;
}