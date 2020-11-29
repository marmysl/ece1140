#include "HardwarePLC.h"

HardwarePLC::HardwarePLC(){
    // take file and store it in string

}

bool HardwarePLC::interpretHWPLC(std::string){
    // variables to store conditions and outputs without overwriting current program
    std::vector<std::string> tempcond;
    std::vector<std::string> tempops;



    return 0;
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


