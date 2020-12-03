#include <vector>
#include <string>
#include "HardwarePLC.h"

HardwarePLC::HardwarePLC(){
}

bool HardwarePLC::interpretHWPLC(QString path){
    // is upload successful
    bool success = 0;

    // variables to store conditions and outputs without overwriting current program
    std::vector<std::string> tempcond;
    std::vector<std::string> tempops;
    std::vector<int> tempblcs;
    std::vector<int> tempopblcs;

    // open and read from file
    std::ifstream plcprogram;
    QFileInfo lfInfo(path);
    plcprogram.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !plcprogram.is_open() ) throw std::invalid_argument ("Unable to open PLC file");

    // read line by line
    std::string line;
    while( getline(plcprogram, line) ) {

        std::stringstream linestream(line);
        std::string conditional;
        std::string condition;
        int blockNum;
        std::string space;
        std::string then;
        std::string result;
        int outputBlock;

        std::cout << line << std::endl;

        std::getline(linestream, conditional, ' ');
        if (conditional != "IF") throw std::invalid_argument ("PLC File is not formatted correctly");

        std::getline(linestream, condition, ' ');
        if ((condition == "!block") || (condition == "block") || (condition == "switch") || (condition == "!switch")) {
            tempcond.push_back(condition);
        }

        linestream >> blockNum;

        // check if this block exists
        bool validID;
        std::vector<int> greenb{0,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74};
        for (unsigned int i = 0; i < greenb.size(); i++) {
            if (blockNum == greenb[i]) validID = 1;
        }
        if (validID != 1) throw std::invalid_argument ("Undefined block in PLC file");

        tempblcs.push_back(blockNum);

        std::getline(linestream, space, ' ');

        std::getline(linestream, then, ' ');
        if (then != "THEN") throw std::invalid_argument ("PLC File is not formatted correctly");

        std::getline(linestream, result, ' ');
        if ((result == "!switch") || (result == "switch") || (result == "red") || (result == "green") || (result == "yellow")){
            tempops.push_back(result);
        }

        linestream >> outputBlock;
        // check if this block exists
        validID = 0;
        for (unsigned int i = 0; i < greenb.size(); i++) {
            if (outputBlock == greenb[i]) validID = 1;
        }
        if (validID != 1) throw std::invalid_argument ("Undefined block in PLC file");

        tempopblcs.push_back(outputBlock);
    }

    // If valid, then temporary conditions and outputs are stored in the conditions and outputs vectors
    setCondition(tempcond);
    setResult(tempops);
    setBlocks(tempblcs);
    setOutputBlocks(tempopblcs);
    success = 1;

    return success;
}

void HardwarePLC::setCondition(std::vector<std::string> newcond){
    for (unsigned int i = 0; i < newcond.size(); i++) {
          conditions.push_back(newcond[i]);
    }
}

void HardwarePLC::setResult(std::vector<std::string> newops){
    for (unsigned int i = 0; i < newops.size(); i++)
        outputs.push_back(newops[i]);
}

void HardwarePLC::setBlocks(std::vector<int> newblcs){
    for (unsigned int i = 0; i < newblcs.size(); i++)
        blockIDs.push_back(newblcs[i]);
}

void HardwarePLC::setOutputBlocks(std::vector<int> newblcs){
    for (unsigned int i = 0; i < newblcs.size(); i++)
        opBlocks.push_back(newblcs[i]);
}

std::vector<std::string> HardwarePLC::getConditions(){
    return conditions;
}

std::vector<std::string> HardwarePLC::getOutputs(){
    return outputs;
}

std::vector<int> HardwarePLC::getBlocks(){
    return blockIDs;
}

std::vector<int> HardwarePLC::getOutputBlocks(){
    return opBlocks;
}



