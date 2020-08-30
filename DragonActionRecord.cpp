#include "DragonActionRecord.h"
#include "dynamicarray.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>



DragonActionRecord::DragonActionRecord(char *newPathName,        // name of the source path
                                       char *newActionName      // name of the action
                                      )
{
    pathName = newPathName;
    actionName = newActionName;

    string seqtemp = string(newPathName)+	// make the name of the seq file
                     string("/")+
                     string(newActionName)+
	    	     string("/")+
	             string(newActionName)+
                     string(".seq");
    seqName = 	&seqtemp[0];

    string wavetemp = string(newPathName)+	// Make the name of the wave file
                      string("/")+
                      string(newActionName)+
                      string("/")+
                      string(newActionName)+
                      string(".wav");
    waveName = &wavetemp[0];

    numberOfSteps = 0;
    fstream sequenceFileHandle;
    sequenceFileHandle.open(seqName, ios::in);
    string lineWithServoValues;

    string actionTypeString;
    getline(sequenceFileHandle,actionTypeString);	// First line contains meta info
    if(actionTypeString=="male")actionType=1;		// convert name to integer
    if(actionTypeString=="female")actionType=2;
    if(actionTypeString=="child")actionType=3;
    if(actionTypeString=="myself")actionType=4;
    if(actionTypeString=="song")actionType=5;
    if(actionTypeString=="scream")actionType=6;

    while(getline(sequenceFileHandle, lineWithServoValues)){	//count the lines
    	numberOfSteps++;
    }
    print();						// Dump the record
    sequence = new DragonActionLine[numberOfSteps];

    sequenceFileHandle.clear();				// Reset the file
    sequenceFileHandle.seekg(0, ios::beg);
    getline(sequenceFileHandle,lineWithServoValues);	// First line contains meta informatie
    int counter = 0;
    while(getline(sequenceFileHandle, lineWithServoValues)){  	// read data from file object and put it into string.
    		     //std::cerr<<"#";
    		     sequence[counter].fillFromString(lineWithServoValues);
    		     counter++;
    }
    std::cerr<<"DragonActionRecord: record stored in memory\n";
}

DragonActionRecord::~DragonActionRecord()
{
    //dtor
}

void DragonActionRecord::print()
{
	std::cerr<<"DragonActionRecord: pathName        = "<<pathName<<endl;
	std::cerr<<"DragonActionRecord: actionName      = "<<actionName<<endl;
	std::cerr<<"DragonActionRecord: seqName         = "<<seqName<<endl;
	std::cerr<<"DragonActionRecord: waveName        = "<<waveName<<endl;
	std::cerr<<"DragonActionRecord: number of steps = "<<numberOfSteps<<endl;
	std::cerr<<"DragonActionRecord: action type for = "<<actionType<<endl;
	std::cerr<<"DragonActionRecord: ---------------------------------------"<<endl;
	
}


string DragonActionRecord::getActionName()
{
	return actionName;
}

string DragonActionRecord::getPathname()
{
	return pathName;
}

string DragonActionRecord::getSeqName()
{
	return seqName;
}

string DragonActionRecord::getWaveName()
{
	return waveName;
}

int DragonActionRecord::getNumberOfSteps()
{
	return numberOfSteps;
}

DragonActionLine* DragonActionRecord::getActionAt(int pos)
{
	return &sequence[pos];
}

int DragonActionRecord::getActionType()
{
	return actionType;
}
