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
using namespace std;

#define FILENAME "output.txt"

PCWorker::PCWorker( string toCrack, int tries) {
    passwordList = loadPasswordList();
    toCrackHashed = crypt(toCrack.c_str(), "qwerty");
    this->tries = tries;
}

void PCWorker::parallelAutomaticAttack(int numberOfThreads) {
    printf("--- Begin automatic parallel attack ---\n");
    for (int i = 0; i < tries; ++i) {
        volatile bool passwordNotFound = true;
         chrono::steady_clock::time_point beginAttack =  chrono::steady_clock::now();
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
                    cout << "Pass #" << i << " -  Thread #" << threadNumber << " - Password found: "
                         << passwordList[j].c_str() << endl;
                }
            }
        }
         chrono::steady_clock::time_point endAttack =  chrono::steady_clock::now();
         cout << "Time elapsed: "
                  <<  chrono::duration_cast< chrono::nanoseconds>(endAttack - beginAttack).count()
                  << " nanoseconds" <<  endl;
        runTimesAutomaticParallel.push_back(
                 chrono::duration_cast< chrono::nanoseconds>(endAttack - beginAttack).count());
    }
    long averageTime = getAverageTime(runTimesAutomaticParallel);
    cout << "--- Automatic parallel attack ended. Average time: " << averageTime << " nanoseconds ---" << endl;
}

void PCWorker::parallelAttack(int numberOfThreads) {
    printf("--- Begin parallel attack ---\n");
    int splitPasswordListRowsPerThread = static_cast<int>(ceil(
            (double) passwordList.size() / (double) numberOfThreads));
    for (int i = 0; i < tries; i++) {
        volatile bool passwordNotFound = true;
         chrono::steady_clock::time_point beginAttack =  chrono::steady_clock::now();
        #pragma omp parallel num_threads(numberOfThreads) shared(passwordNotFound)
        {
            struct crypt_data threadSafeCryptData;
            threadSafeCryptData.initialized = 0;
            int threadNumber = omp_get_thread_num();
            for (int j = splitPasswordListRowsPerThread * threadNumber;
                 j < splitPasswordListRowsPerThread * (threadNumber + 1) - 1; j++) {
                if (j < passwordList.size() && passwordNotFound) {
                    char *inPlaceHashedPassword = crypt_r(passwordList[j].c_str(), "qwerty", &threadSafeCryptData);
                    if (inPlaceHashedPassword == toCrackHashed) {
                        passwordNotFound = false;
                        cout << "Pass #" << i << " -  Thread #" << threadNumber << " - Password found: "
                        << passwordList[j].c_str() << endl;
                        break;
                    }
                } else {
                    break;
                }
            }
        }
         chrono::steady_clock::time_point endAttack =  chrono::steady_clock::now();
         cout << "Time elapsed: " <<  chrono::duration_cast< chrono::nanoseconds>(
                endAttack - beginAttack).count() << " nanoseconds" <<  endl;
        runTimesParallel.push_back(
                 chrono::duration_cast< chrono::nanoseconds>(endAttack - beginAttack).count());
    }
    long averageTime = getAverageTime(runTimesParallel);
    cout << "--- Parallel attack ended. Average time: " << averageTime << " nanoseconds ---" << endl;
}

void PCWorker::sequentialAttack() {
     cout << "--- Begin sequential attack ---" <<  endl;
    for (int i = 0; i < tries; ++i) {
         chrono::steady_clock::time_point beginAttack =  chrono::steady_clock::now();
        for ( string &password: passwordList) {
             string inPlaceHashedPassword = crypt(password.c_str(), "qwerty");
            if (inPlaceHashedPassword == toCrackHashed) {
                 chrono::steady_clock::time_point endAttack =  chrono::steady_clock::now();
                 cout << "Pass #" << i << " - Password found: " << password.c_str() << endl;
                 cout << "Time elapsed: "
                          <<  chrono::duration_cast< chrono::nanoseconds>(endAttack - beginAttack).count()
                          << " nanoseconds" <<  endl;
                runTimesSequential.push_back(
                         chrono::duration_cast< chrono::nanoseconds>(endAttack - beginAttack).count());
                break;
            }
        }
    }
    long averageTime = getAverageTime(runTimesSequential);
    cout << "--- Sequential attack ended. Average time: " << averageTime << " nanoseconds ---" << endl;
}


 vector< string> PCWorker::loadPasswordList() {
     vector< string> vec;
     ifstream file(FILENAME);
    if (!file) {
        print("Can't read the password list file");
        exit(1);
    }
    if (file.is_open()) {
         string line;
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

void PCWorker::print( string toPrint) {
     cout << toPrint <<  endl;
}

void PCWorker::printVector( vector< string> &vec) {
    for (auto i = vec.begin(); i <= vec.end(); i++) {
         cout << *i <<  endl;
    }
}

long PCWorker::getAverageTime( vector<long> &vec) {
    long average = 0;
    for (long &time: vec) {
        average += time;
    }
    return average / tries;
}

 vector<long> PCWorker::getRunTimesSequential() {
    return runTimesSequential;
}

 vector<long> PCWorker::getRunTimesParallel() {
    return runTimesParallel;
}

 vector<long> PCWorker::getRunTimesAutomaticParallel() {
    return runTimesAutomaticParallel;
}

 vector<double> PCWorker::getSpeedUpSequentialToParallel() {
    return speedUpSequentialToParallel;
}

 vector<double> PCWorker::getSpeedUpSequentialToAutomaticParallel() {
    return speedUpSequentialToAutomaticParallel;
}

void PCWorker::reset() {
    runTimesAutomaticParallel = {};
    runTimesParallel = {};
    speedUpSequentialToAutomaticParallel = {};
    speedUpSequentialToParallel = {};
    cout.flush();
}