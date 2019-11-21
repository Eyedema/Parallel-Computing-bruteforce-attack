//
// Created by eyedema on 19/11/19.
//

#ifndef PC_PROJECT_CSVWRITER_H
#define PC_PROJECT_CSVWRITER_H

#include <string>
#include <vector>

class CSVWriter {
public:
    CSVWriter(std::string name, std::vector<std::string> vector);
    void writeCSV(std::vector<std::vector<long>> dataset,
                  std::vector<std::vector<double>> dataset2, int tries, std::string password, int number);

private:
    std::string filename;
};


#endif //PC_PROJECT_CSVWRITER_H
