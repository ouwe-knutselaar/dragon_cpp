#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <dirent.h>
#include <fstream>
#include <ios>
#include "DragonFileManager.h"
#include "DragonActionRecord.h"
#include <ostream>

using namespace std;

DragonFileManager::DragonFileManager()
{
    cout<<"DragonFileManager: Starting the DragonFileManager"<<endl;
}

DragonFileManager::~DragonFileManager()
{
    //dtor
}

//vector<string> DragonFileManager::__dirList;


void DragonFileManager::loadActionNamesList()
{
	cout<<"DragonFileManager:  open dir "<<__currentpath<<endl;

    struct dirent *ent;
    DIR *dir;
    dir = opendir(__currentpath);

      while( (ent = readdir(dir)) != NULL)
      {
          if( ( ent->d_type == DT_DIR ) & ( ent->d_name[0] != '.') )
          {
              DragonActionRecord temp(__currentpath,ent->d_name);
              __dirList.push_back(temp);
          }
      };

        for(unsigned int tel = 0 ;tel<__dirList.size();tel++)__dirList[tel].print();
}


void DragonFileManager::setCurrentPath(char* newPath)
{
    __currentpath = newPath;
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



void DragonFileManager::loadAction(string actionName,unsigned int  **stepList,int *stepListSize)
{
	cout<<"DragonFileManager: search action -"<<actionName<<"- "<<endl;

	// Find the action
	string seqFileName = "";
	for(DragonActionRecord record : __dirList)
	{
		if(record.getActionName() == actionName)seqFileName = record.getSeqName();
	}
	cout<<"DragonFileManager: load action "<<seqFileName<<endl;

	  // Load the sequence file in a temp list
	  string line;
	  vector<string> tempList;
	  ifstream seqFile(seqFileName,ios::in);
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



