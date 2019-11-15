//
// Created by ublud on 11/15/2019.
//

#include <fstream>
#include <iostream>
#include <crypt.h>
#include <chrono>
#include "PCWorker.h"
#define FILENAME "passdict.txt"

PCWorker::PCWorker(std::string toCrack, int tries) {
    passwordList = loadPasswordList();
    this->toCrack = toCrack;
    this->toCrackHashed = crypt(toCrack.c_str(), "qwerty");
    this->tries = tries;
}

void PCWorker::sequentialAttack() {
    for (int i = 0; i < tries; ++i) {
        std::chrono::steady_clock::time_point beginAttack = std::chrono::steady_clock::now();
        for(std::string& password: passwordList){
            std::string inPlaceHashedPassword = crypt(password.c_str(), "qwerty");
            if(inPlaceHashedPassword == toCrackHashed){
                std::chrono::steady_clock::time_point endAttack = std::chrono::steady_clock::now();
                printf("Pass #%d - Password found: %s - ", i, password.c_str());
                std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds> (endAttack - beginAttack).count() << " nanoseconds" << std::endl;
                this->runTimesSequential.push_back(std::chrono::duration_cast<std::chrono::nanoseconds> (endAttack - beginAttack).count());
            }
        }
    }
    long averageTime = getAverageTime(runTimesSequential);
    printf("Sequential attack ended. Average time: %d nanoseconds", averageTime);
}

std::vector<std::string> PCWorker::loadPasswordList() {
    std::vector<std::string> vec;
    std::ifstream file(FILENAME);
    if (!file) {
        print("Can't read the password list file");
        exit(1);
    }
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            vec.push_back(line);
        }
        file.close();
    }
    return vec;
}

void PCWorker::print(std::string toPrint) {
    std::cout << toPrint << std::endl;
}

void PCWorker::printVector(std::vector<std::string> &vec) {
    for (auto i = vec.begin(); i <= vec.end(); i++) {
        std::cout << *i << std::endl;
    }
}

long PCWorker::getAverageTime(std::vector<long> &vec){
    long average = 0;
    for(long& time: vec){
        average += time;
    }
    return average/tries;
}