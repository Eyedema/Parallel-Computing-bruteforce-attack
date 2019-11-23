//
// Created by ublud on 11/15/2019.
//

#include <fstream>
#include <iostream>
#include <crypt.h>
#include <chrono>
#include <omp.h>
#include <string>
#include <cmath>
#include "PCWorker.h"

#define FILENAME "output.txt"

PCWorker::PCWorker(std::string toCrack, int tries) {
    passwordList = loadPasswordList();
    toCrackHashed = crypt(toCrack.c_str(), "qwerty");
    this->tries = tries;
}

void PCWorker::parallelAutomaticAttack(int numberOfThreads) {
    printf("--- Begin automatic parallel attack ---\n");
    for (int i = 0; i < tries; ++i) {
        volatile bool passwordNotFound = true;
        std::chrono::steady_clock::time_point beginAttack = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(numberOfThreads) shared(passwordNotFound)
        {
            struct crypt_data threadSafeCryptData;
            threadSafeCryptData.initialized = 0;
            int threadNumber = omp_get_thread_num();
#pragma omp for
            for (int j = 0; j < passwordList.size(); j++) {
                if (!passwordNotFound) continue;
                char *inPlaceHashedPassword = crypt_r(passwordList[j].c_str(), "qwerty", &threadSafeCryptData);
                if (inPlaceHashedPassword == toCrackHashed) {
                    passwordNotFound = false;
                    printf("Pass #%d - Thread #%d - Password found: %s - ", i, threadNumber,
                           passwordList[j].c_str());
                }
            }
        }
        std::chrono::steady_clock::time_point endAttack = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(endAttack - beginAttack).count()
                  << " nanoseconds" << std::endl;
        runTimesAutomaticParallel.push_back(
                std::chrono::duration_cast<std::chrono::nanoseconds>(endAttack - beginAttack).count());
    }
    long averageTime = getAverageTime(runTimesAutomaticParallel);
    printf("--- Automatic parallel attack ended. Average time: %ld nanoseconds ---\n", averageTime);
}

void PCWorker::parallelAttack(int numberOfThreads) {
    printf("--- Begin parallel attack ---\n");
    int splitPasswordListRowsPerThread = static_cast<int>(ceil(
            (double) passwordList.size() / (double) numberOfThreads));
    for (int i = 0; i < tries; i++) {
        volatile bool passwordNotFound = true;
        std::chrono::steady_clock::time_point beginAttack = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(numberOfThreads) shared(passwordNotFound)
        {
            struct crypt_data threadSafeCryptData;
            threadSafeCryptData.initialized = 0;
            int threadNumber = omp_get_thread_num();
            for (int j = splitPasswordListRowsPerThread * threadNumber;
                 j < splitPasswordListRowsPerThread * (threadNumber + 1); j++) {
                if (j < passwordList.size() && passwordNotFound) {
                    char *inPlaceHashedPassword = crypt_r(passwordList[j].c_str(), "qwerty", &threadSafeCryptData);
                    if (inPlaceHashedPassword == toCrackHashed) {
                        passwordNotFound = false;
                        printf("Pass #%d - Thread #%d - Password found: %s - ", i, threadNumber,
                               passwordList[j].c_str());
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        std::chrono::steady_clock::time_point endAttack = std::chrono::steady_clock::now();
        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::nanoseconds>(
                endAttack - beginAttack).count() << " nanoseconds" << std::endl;
        runTimesParallel.push_back(
                std::chrono::duration_cast<std::chrono::nanoseconds>(endAttack - beginAttack).count());
    }
    long averageTime = getAverageTime(runTimesParallel);
    printf("--- Parallel attack ended. Average time: %ld nanoseconds ---\n", averageTime);
}

void PCWorker::sequentialAttack() {
    std::cout << "--- Begin sequential attack ---" << std::endl;
    for (int i = 0; i < tries; ++i) {
        std::chrono::steady_clock::time_point beginAttack = std::chrono::steady_clock::now();
        for (std::string &password: passwordList) {
            std::string inPlaceHashedPassword = crypt(password.c_str(), "qwerty");
            if (inPlaceHashedPassword == toCrackHashed) {
                std::chrono::steady_clock::time_point endAttack = std::chrono::steady_clock::now();
                std::cout << "Pass #" << i << " - Password found: " << password.c_str();
                std::cout << "Time elapsed: "
                          << std::chrono::duration_cast<std::chrono::nanoseconds>(endAttack - beginAttack).count()
                          << " nanoseconds" << std::endl;
                runTimesSequential.push_back(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(endAttack - beginAttack).count());
                break;
            }
        }
    }
    long averageTime = getAverageTime(runTimesSequential);
    printf("--- Sequential attack ended. Average time: %ld nanoseconds ---\n", averageTime);
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

void PCWorker::computeSpeedUp() {
    int i = 0;
    for (long &result : runTimesSequential) {
        speedUpSequentialToParallel.push_back(double(result) / double(runTimesParallel[i]));
        speedUpSequentialToAutomaticParallel.push_back(double(result) / double(runTimesAutomaticParallel[i]));
        i++;
    }
}

void PCWorker::print(std::string toPrint) {
    std::cout << toPrint << std::endl;
}

void PCWorker::printVector(std::vector<std::string> &vec) {
    for (auto i = vec.begin(); i <= vec.end(); i++) {
        std::cout << *i << std::endl;
    }
}

long PCWorker::getAverageTime(std::vector<long> &vec) {
    long average = 0;
    for (long &time: vec) {
        average += time;
    }
    return average / tries;
}

std::vector<long> PCWorker::getRunTimesSequential() {
    return runTimesSequential;
}

std::vector<long> PCWorker::getRunTimesParallel() {
    return runTimesParallel;
}

std::vector<long> PCWorker::getRunTimesAutomaticParallel() {
    return runTimesAutomaticParallel;
}

std::vector<double> PCWorker::getSpeedUpSequentialToParallel() {
    return speedUpSequentialToParallel;
}

std::vector<double> PCWorker::getSpeedUpSequentialToAutomaticParallel() {
    return speedUpSequentialToAutomaticParallel;
}

void PCWorker::reset() {
    runTimesAutomaticParallel = {};
    runTimesParallel = {};
    speedUpSequentialToAutomaticParallel = {};
    speedUpSequentialToParallel = {};
}