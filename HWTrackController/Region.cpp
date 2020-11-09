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
}


