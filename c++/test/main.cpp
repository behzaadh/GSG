#include <iostream>
#include "GSGfile.h"

int main() {
    GsgOutput out = readGsgAll("reservoir.GSG");
    /*
    for (int i = 0; i < out.headers.size(); ++i) {
        if (out.headers[i] == "PRESSURE") {
            for (size_t j = 0; j < out.dataVector[i].doubleData.size(); j++)
            {
                std::cout << out.dataVector[i].doubleData[j] << std::endl;
            }
            
        }
    }
    */
    // Test case 2: Non-empty data
    std::vector<std::string> keywords = {"PRESSURE", "TEMPERATURE"};
    GsgOutput out2;
    GsgData data;
    for (size_t i = 0; i < 828; i++)
    {
        data.doubleData.push_back(i);
    }
    out2.dataVector.push_back(data);
    out2.dataVector.push_back(data);
    writeGsg("reservoir.GSG", keywords, out2);

    GsgOutput out3 = readGsgAll("reservoir.GSG");
    /*
    for (int i = 0; i < out3.headers.size(); ++i) {
        if (out3.headers[i] == "TEMPERATURE" || out3.headers[i] == "PRESSURE") {
            for (size_t j = 0; j < out3.dataVector[i].doubleData.size(); j++)
            {
                std::cout << out3.dataVector[i].doubleData[j] << std::endl;
            }
            
        }
    }
    */
}
