#include "DragonFileManager.h"
#include "DragonActionRecord.h"

#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <time.h>


DragonFileManager::DragonFileManager()
{
    cerr<<"DragonFileManager: Starting the DragonFileManager"<<endl;
    srand (time(NULL));
}

DragonFileManager::~DragonFileManager()
{
    //dtor
}

//vector<string> DragonFileManager::__dirList;


void DragonFileManager::loadActionNamesList()
{
	std::cerr<<"DragonFileManager: open dir "<<currentpath_<<endl;

    struct dirent *ent;
    DIR *dir;
    dir = opendir(currentpath_);

    while( (ent = readdir(dir)) != NULL)
    {
        if( ( ent->d_type == DT_DIR ) & ( ent->d_name[0] != '.') )
        {
            DragonActionRecord temp(currentpath_,ent->d_name);
            dirList_.push_back(temp);
        }
    };

    cerr<<"DragonFileManager: loaded "<<dirList_.size()<<" actions\n";
}


void DragonFileManager::setCurrentPath(char* newPath)
{
    currentpath_ = newPath;
}


unsigned int* DragonFileManager::seqLineToIntPtr(string line)
{
	unsigned int seqStep[16];
	for(int tel = 0;tel<16;tel++)
	{
		seqStep[tel] = stoi(line.substr(tel*4,4+tel*4));
	}
	return seqStep;
}


void DragonFileManager::defineRandomAction(int actionType)
{
	currentAction_ = (int)rand()%dirList_.size();
}


string DragonFileManager::getCurrentWaveFile()
{
	cerr<<"DragonFileManager: ask for "<<dirList_[currentAction_].getWaveName()<<endl;
	return dirList_[currentAction_].getWaveName();
}

string DragonFileManager::getCurrentSequenceFile()
{
	return dirList_[currentAction_].getSeqName();
}

int  DragonFileManager::getCurrentSequenceSteps()
{
	return dirList_[currentAction_].getNumberOfSteps();
}

DragonActionLine* DragonFileManager::getCurrentActionServoSteps(int pos)
{
	return dirList_[currentAction_].getActionAt(pos);
}

