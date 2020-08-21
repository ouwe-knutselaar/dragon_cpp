#include "DragonActionLine.h"
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
	for(int tel = 0;tel<15;tel++)
		{
		servovalues[tel] = stoi(serveoValues.substr(tel*4,4+tel*4));
		}
}

