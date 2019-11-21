//
// Created by eyedema on 19/11/19.
//

#include <fstream>
#include <sys/stat.h>
#include "CSVWriter.h"

void CSVWriter::writeCSV(std::vector<std::vector<long>> dataset,
                         std::vector<std::vector<double>> dataset2, int tries, std::string password, int number) {

    std::ofstream myFile(filename, std::ios_base::app);

// Send data to the stream

for (int k = 0; k < tries; ++k) {
    for (int i = 0; i < 3; ++i) {
        myFile << dataset.at(i).at(k);
        myFile << ",";
    }
    for (int i = 0; i < 2; ++i) {
        myFile << dataset2.at(i).at(k);
        if (i != 1) myFile << ",";
    }
    myFile << ","+std::to_string(tries)+","+std::to_string(number)+","+password+"\n";
}


// Close the file
    myFile.close();
}
CSVWriter::CSVWriter(std::string filename, std::vector<std::string> vector) {
    this->filename=filename;
    mkdir("./results", 0777);
    std::ofstream myFile(filename, std::ios_base::app);

// Send column names to the stream
    for (int i = 0; i < vector.size(); ++i) {
        myFile << vector[i];
        if (i != vector.size() - 1) myFile << ",";
    }
    myFile << "\n";
// Close the file
    myFile.close();
}
