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

private:
    std::vector<std::string> loadPasswordList();
    void print(std::string toPrint);
    void printVector(std::vector<std::string> &vec);
    std::vector<std::string> passwordList;
    std::string toCrack;
    std::string toCrackHashed;
    int tries;
    std::vector<long> runTimesSequential;
    long getAverageTime(std::vector<long> &vec);
};


#endif //PC_PROJECT_PCWORKER_H
