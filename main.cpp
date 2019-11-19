#include <string>
#include <vector>
#include <cstdlib>
#include <sys/resource.h>
#include "PCWorker.h"
#include "CSVWriter.h"

int main(int argc, char **argv) {
    PCWorker PCWorker(argv[1], std::strtol(argv[2], nullptr, 0));
    std::vector<int> numberOfThreads = {16, 5000, 10000};
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
        CSVWriter CSVWriter;
        CSVWriter.writeCSV("PC Results "+std::to_string(number)+".csv", values, valuesDouble, std::strtol(argv[2], nullptr, 0));
    }

    return 0;
}