//This file contains the definitions of the member functions.
#include <iostream>
#include <vector>
#include "TrackController.h"


//using namespace std;

TrackController::TrackController(){
	region = 1;
	block_count = 15;
	section_length = 5;
	section_count = 3;
	cntrl_sections.push_back('A');
	cntrl_sections.push_back('B');
	cntrl_sections.push_back('C');
	
	for(int i = 1; i <= block_count; i++)
		cntrl_blocks.push_back(i);
	
	cntrl_switches.push_back(5);
	cntrl_switches.push_back(6);
	cntrl_switches.push_back(11);
    //TrackModel::Route *blueLine = initTestLayout();
	

}

int TrackController::getResult() {
	std::cout << "region: " << region << "\n\n";
	std::cout << "sections: ";
	for ( auto i = cntrl_sections.begin(); i != cntrl_sections.end(); ++i) 
        std::cout << *i << " ";
    std::cout << "\n\nblocks: ";
    for ( auto i = cntrl_blocks.begin(); i != cntrl_blocks.end(); ++i) 
        std::cout << *i << " ";
    std::cout << "\n\nswitches: ";
    for ( auto i = cntrl_switches.begin(); i != cntrl_switches.end(); ++i) 
        std::cout << *i << " ";
        
        return 0;
}



