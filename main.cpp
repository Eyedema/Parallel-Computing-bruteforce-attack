#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define FILENAME "passdict.txt"

void printVector(std::vector<std::string> &vec);
void print(std::string toPrint);

int main() {

    std::vector<std::string> vec;

    std::ifstream file(FILENAME);
    if (!file) {
        print("Can't read the password list file");
        return 0;
    }
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            vec.push_back(line);
        }
        file.close();
    }
    printVector(vec);
    return 0;
}

void printVector(std::vector<std::string> &vec) {
    for (auto i = vec.begin(); i <= vec.end(); i++) {
        std::cout << *i << std::endl;
    }
}

void print(std::string toPrint) {
    std::cout << toPrint << std::endl;
}
