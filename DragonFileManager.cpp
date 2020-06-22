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


using namespace std;

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
	cout<<"DragonFileManager:  open dir "<<currentpath_<<endl;

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



void DragonFileManager::getCurrentActionSteps(unsigned int **stepList,int *stepListSize)
{
	cout<<"DragonFileManager: search action -"<<dirList_[currentAction_].getActionName()<<"- "<<endl;
	cout<<"DragonFileManager: load action "<<dirList_[currentAction_].getSeqName()<<endl;

	  // Load the sequence file in a temp list
	  string line;
	  vector<string> tempList;
	  ifstream seqFile(dirList_[currentAction_].getSeqName(),ios::in);
	  for(string line ; getline(seqFile,line); )tempList.push_back(line);

	    // fill the steplist
	    stepList = new unsigned int*[tempList.size()];
	    *stepListSize = (unsigned int)tempList.size();
	    for(unsigned int tel = 0;tel<tempList.size();tel++)
	    {
	  	    stepList[tel] = seqLineToIntPtr(tempList[tel]);
	    }

	      cout<<"DragonFileManager: load action finished"<<endl;
	      cout<<"DragonFileManager: contains "<<tempList.size()<<" steps"<<endl;
}

void DragonFileManager::defineRandomAction(int actionType)
{
	currentAction_ = rand()%dirList_.size();


}

string DragonFileManager::getCurrectWaveFile()
{
	return dirList_[currentAction_].getWaveName();
}

