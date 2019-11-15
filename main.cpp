#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <crypt.h>
#include "PCWorker.h"

int main(int argc, char** argv) {

    PCWorker PCWorker(argv[1]); // vjht1051
    PCWorker.sequentialAttack();
    return 0;
}