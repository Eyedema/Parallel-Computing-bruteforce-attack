//
// Created by ublud on 11/15/2019.
//

#ifndef PC_PROJECT_PCWORKER_H
#define PC_PROJECT_PCWORKER_H


#include <string>
#include <vector>

class PCWorker {
public:
    PCWorker(std::string toCrack, int tries);
    void sequentialAttack();
    void parallelAttack(int numberOfThreads);
    void parallelAutomaticAttack(int numberOfThreads);
    std::vector<long> getRunTimesSequential();
    std::vector<long> getRunTimesParallel();
    std::vector<long> getRunTimesAutomaticParallel();
    std::vector<double> getSpeedUpSequentialToParallel();
    std::vector<double> getSpeedUpSequentialToAutomaticParallel();
    void computeSpeedUp();

    void reset();

private:
    std::vector<std::string> loadPasswordList();
    void print(std::string toPrint);
    void printVector(std::vector<std::string> &vec);
    std::vector<std::string> passwordList;
    std::string toCrackHashed;
    int tries;
    std::vector<long> runTimesSequential;
    std::vector<long> runTimesParallel;
    std::vector<long> runTimesAutomaticParallel;
    std::vector<double> speedUpSequentialToParallel;
    std::vector<double> speedUpSequentialToAutomaticParallel;
    long getAverageTime(std::vector<long> &vec);

};


#endif //PC_PROJECT_PCWORKER_H
