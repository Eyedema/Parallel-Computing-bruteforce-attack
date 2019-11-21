//
// Created by eyedema on 19/11/19.
//

#include <fstream>
#include <sys/stat.h>
#include "CSVWriter.h"

void CSVWriter::writeCSV(std::string filename, std::vector<std::pair<std::string, std::vector<long>>> dataset,
                         std::vector<std::pair<std::string, std::vector<double>>> dataset2, int tries) {

    mkdir("./results", 0777);
    std::ofstream myFile(filename);

// Send column names to the stream
    for (int j = 0; j < dataset.size(); ++j) {
        myFile << dataset.at(j).first;
        myFile << ",";
    }
    for (int j = 0; j < dataset2.size(); ++j) {
        myFile << dataset2.at(j).first;
        if (j != dataset2.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

// Send data to the stream

for (int k = 0; k < tries; ++k) {
    for (int i = 0; i < 3; ++i) {
        myFile << dataset.at(i).second.at(k);
        myFile << ",";
    }
    for (int i = 0; i < 2; ++i) {
        myFile << dataset2.at(i).second.at(k);
        if (i != 1) myFile << ",";
    }
    myFile << "\n";
}


// Close the file
    myFile.close();
}