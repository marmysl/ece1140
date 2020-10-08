#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Region.hpp"

using namespace std;

//Constructor
Region :: Region() {
	region = 1;

	for (int i = 1; i <= 15; i++) 
        blocks.push_back(i); 

	sections.push_back("A");
	sections.push_back("B");
	sections.push_back("C");

	cout << "blocks: "; 
	for (auto it = blocks.begin(); it != blocks.end(); it++) 
        cout << *it << " "; 

    cout << "\nsections: ";
    for (auto nn = sections.begin(); nn != sections.end(); nn++) 
        cout << *nn << " "; 

    currentBlock = blocks.front();
    currentSection = sections.front();
    route = "Blue Line";
    cout << "\nCurrent Block: " << currentBlock << endl;
    cout << "Section: " << currentSection << endl;
    cout << "Route: " << route << endl;

    TrackModel::Route *blueLine = initTestLayout();
}

void Region :: initialize(CTCSignals &c1) {
 	for (int i=0; i < c1.speedCTC.size(); i++) 
        suggestedSpeed.push_back(c1.speedCTC[i]); 
  
    cout << "Suggested speed (from the CTC signal class) elements are : "; 
    for (int i=0; i<suggestedSpeed.size(); i++) 
        cout << suggestedSpeed[i] << " "; 
    cout<< endl; 

    for (int i=0; i < c1.authCTC.size(); i++) 
        authority.push_back(c1.authCTC[i]); 
  
    cout << "Authority (from CTC class) elements are : "; 
    for (int i=0; i<authority.size(); i++) 
        cout << authority[i] << " "; 
    cout<< endl; 

    setCircuit();
}

std::string Region::getRoute() const {
    return route;
}

std::string Region::getSection() const {
	return currentSection;
}

int Region::getCurrentBlock() const {
	return currentBlock;
} 
    
int Region::getSuggestedSpeed() const{
	return suggestedSpeed[currentBlock];
}

int Region::getCommandedSpeed() const {
	return commandedSpeed[currentBlock];
}

int Region::getAuthority() const{
	return authority[currentBlock];
}
  
int Region::getSpeedLimit() const{
	return speedLimit[currentBlock];
}
   
void Region::setSection(std::string val) {
	currentSection = val;
}

void Region::setCurrentBlock(int val) {
	currentBlock = val;
}

void Region :: setCommandedSpeed(int blockID, int val) {
	commandedSpeed[blockID] = val;
}

void Region :: setAuthority(int blockID, int val) {
	authority[blockID] = val;
}
 
void Region :: setCircuit() {
	for (int i = 0; i < blocks.size(); i++){
		cout << " In setCircuit, show me block: " << blocks[i] << endl;
		TrackModel::TrackCircuitData tcdata = TrackModel::TrackCircuitData::fromFloat(suggestedSpeed[i],authority[i]);
		TrackModel::setTrackCircuit(route, blocks[i], tcdata);
	}
}