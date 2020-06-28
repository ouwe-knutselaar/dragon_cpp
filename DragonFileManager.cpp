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
    cout<<"DragonFileManager: Starting the DragonFileManager"<<endl;
    srand (time(NULL));
}

DragonFileManager::~DragonFileManager()
{
    //dtor
}

//vector<string> DragonFileManager::__dirList;


void DragonFileManager::loadActionNamesList()
{
	std::cout<<"DragonFileManager:  open dir "<<currentpath_<<endl;

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

        for(unsigned int tel = 0 ;tel<dirList_.size();tel++)dirList_[tel].print();
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
	return dirList_[currentAction_].getWaveName();
}

string DragonFileManager::getCurrentSequenceFile()
{
	return dirList_[currentAction_].getSeqName();
}

