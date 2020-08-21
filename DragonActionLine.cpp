#include "DragonActionLine.h"
#include <iostream>
#include <string>

using namespace std;


DragonActionLine::DragonActionLine() {
	// TODO Auto-generated constructor stub
}


DragonActionLine::~DragonActionLine() {
	// TODO Auto-generated destructor stub
}


unsigned int* DragonActionLine::getServoValues()
{
	return servovalues;
}


void DragonActionLine::fillFromString(string serveoValues)
{
	std::cerr<<"DragonActionLine: load line "<<serveoValues<<" \n" ;
	for(int tel = 0;tel<15;tel++)
		{
		 std::cerr<<"val: "<<serveoValues.substr(tel*4,4)<<"\n";
		 servovalues[tel] = stoi(serveoValues.substr(tel*4,4));
		}
}

