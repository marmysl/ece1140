#ifndef HARDWAREPLC_H
#define HARDWAREPLC_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFileInfo>

class HardwarePLC {
    private:
        std::vector<std::string> conditions;
        std::vector<std::string> outputs;
        std::vector<int> blockIDs;
        std::vector<int> opBlocks;
    public:
       HardwarePLC();
       bool interpretHWPLC(QString);
       void setCondition(std::vector<std::string>);
       void setResult(std::vector<std::string>);
       void setBlocks(std::vector<int>);
       void setOutputBlocks(std::vector<int>);
       std::vector<std::string> getConditions();
       std::vector<std::string> getOutputs();
       std::vector<int> getBlocks();
       std::vector<int> getOutputBlocks();
};

#endif // HARDWAREPLC_H
