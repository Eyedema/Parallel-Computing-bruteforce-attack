//
// Created by eyedema on 19/11/19.
//

#ifndef PC_PROJECT_CSVWRITER_H
#define PC_PROJECT_CSVWRITER_H

#include <string>
#include <vector>

class CSVWriter {
public:
    void writeCSV(std::string filename, std::vector<std::pair<std::string, std::vector<long>>> dataset,
                  std::vector<std::pair<std::string, std::vector<double>>> dataset2, int tries);
};


#endif //PC_PROJECT_CSVWRITER_H
