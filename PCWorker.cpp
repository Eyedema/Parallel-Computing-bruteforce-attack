//
// Created by ublud on 11/15/2019.
//

#include <fstream>
#include <iostream>
#include <crypt.h>
#include "PCWorker.h"
#define FILENAME "passdict.txt"

PCWorker::PCWorker(std::string toCrack) {
    passwordList = loadPasswordList();
    this->toCrack = toCrack;
    this->toCrackHashed = crypt(toCrack.c_str(), "qwerty");
}

void PCWorker::sequentialAttack() {
    for(std::string& password: passwordList){
        std::string inPlaceHashedPassword = crypt(password.c_str(), "qwerty");
        if(inPlaceHashedPassword == toCrackHashed){
            print("Password found: "+password);
        }
    }
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