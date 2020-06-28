#include "DragonActionLine.h"
#include <string>

using namespace std;


DragonActionLine::DragonActionLine() {
	// TODO Auto-generated constructor stub
}


DragonActionLine::~DragonActionLine() {
	// TODO Auto-generated destructor stub
}


void DragonActionLine::setValue(int pos, int value)
{
	servovalues[pos]=value;
}


int DragonActionLine::getValue(int pos)
{
	return servovalues[pos];
}


void DragonActionLine::fillFromString(string serveoValues)
{
	for(int tel = 0;tel<16;tel++)
		{
		servovalues[tel] = stoi(serveoValues.substr(tel*4,4+tel*4));
		}
}

