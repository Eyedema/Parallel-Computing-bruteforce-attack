#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <crypt.h>
#include <cstdlib>
#include "PCWorker.h"

int main(int argc, char** argv) {

    PCWorker PCWorker(argv[1], std::strtol(argv[2], nullptr, 0)); // vjht1051
    PCWorker.sequentialAttack();
    return 0;
}