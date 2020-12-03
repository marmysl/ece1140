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
       bool InterpretHWPLC(QString);
       void SetCondition(std::vector<std::string>);
       void SetResult(std::vector<std::string>);
       void SetBlocks(std::vector<int>);
       void SetOutputBlocks(std::vector<int>);
       std::vector<std::string> GetConditions();
       std::vector<std::string> GetOutputs();
       std::vector<int> GetBlocks();
       std::vector<int> GetOutputBlocks();
};

#endif // HARDWAREPLC_H
