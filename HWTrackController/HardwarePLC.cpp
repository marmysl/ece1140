#include "HardwarePLC.h"

HardwarePLC::HardwarePLC(){
    // take file and store it in string

}

void HardwarePLC::interpretHWPLC(QString path){

    // variables to store conditions and outputs without overwriting current program
    std::vector<std::string> tempcond;
    std::vector<std::string> tempops;

    std::ifstream plcprogram;
    QFileInfo lfInfo(path);
    plcprogram.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !plcprogram.is_open() ) throw std::invalid_argument ("Unable to open PLC file");

    std::string line;

    while( getline(plcprogram, line) ) {

        std::stringstream linestream(line);
        std::string conditional;
        std::string condition;
        int blockNum;
        std::string space;
        std::string then;
        std::string result;

        std::cout << "PLC: " << line << std::endl;

        std::getline(linestream, conditional, ' ');
        if (conditional != "IF") throw std::invalid_argument ("PLC File is not formatted correctly");

        std::getline(linestream, condition, ' ');
        if ((condition == "!block") || (condition == "block")) {
            tempcond.push_back(condition);
        }

        linestream >> blockNum;
        // does blockNum exist in this program

        std::getline(linestream, space, ' ');

        std::getline(linestream, then, ' ');
        if (then != "THEN") throw std::invalid_argument ("PLC File is not formatted correctly");

        std::getline(linestream, result, ' ');
        if ((condition == "!switch") || (condition == "switch")) {
            tempcond.push_back(condition);
        }
    }
}

void HardwarePLC::setCondition(std::vector<std::string> newcond){
    conditions = newcond;
}

void HardwarePLC::setResult(std::vector<std::string> newops){
    outputs = newops;
}

std::vector<std::string> HardwarePLC::getConditions(){
    return conditions;
}

std::vector<std::string> HardwarePLC::getOutputs(){
    return outputs;
}


