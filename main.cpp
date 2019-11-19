#include <string>
#include <vector>
#include <cstdlib>
#include "PCWorker.h"
#include "CSVWriter.h"

int main(int argc, char **argv) {
    PCWorker PCWorker(argv[1], std::strtol(argv[2], nullptr, 0)); // password: vjht1051, 10 tries
    PCWorker.sequentialAttack();
    PCWorker.parallelAttack(500);
    PCWorker.parallelAutomaticAttack(500);
    PCWorker.computeSpeedUp();
    std::vector<std::pair<std::string, std::vector<long>>> values = {{"Run Times Sequential",         PCWorker.getRunTimesSequential()},
                                                                     {"Run Times Parallel",           PCWorker.getRunTimesParallel()},
                                                                     {"Run Times Automatic Parallel", PCWorker.getRunTimesAutomaticParallel()}};

    std::vector<std::pair<std::string, std::vector<double>>> valuesDouble = {{"Speed up from Sequential to Parallel",           PCWorker.getSpeedUpSequentialToParallel()},
                                                                             {"Speed up from Sequential to Automatic Parallel", PCWorker.getSpeedUpSequentialToAutomaticParallel()}};
CSVWriter CSVWriter;
CSVWriter.writeCSV("PC Results.csv", values, valuesDouble, std::strtol(argv[2], nullptr, 0));
return 0;
}