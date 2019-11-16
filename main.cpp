#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <crypt.h>
#include <cstdlib>
#include "PCWorker.h"

int main(int argc, char** argv) {
    PCWorker PCWorker(argv[1], std::strtol(argv[2], nullptr, 0)); // password: vjht1051, 10 tries
    PCWorker.sequentialAttack();
    PCWorker.parallelAttack(4);
    return 0;
}