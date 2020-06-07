#include "DragonActionRecord.h"
#include <iostream>
#include <string>


using namespace std;

DragonActionRecord::DragonActionRecord(char *newPathName,        // name of the source path
                                       char *newActionName      // name of the action
                                      )
{
    pathName = newPathName;
    actionName = newActionName;

      string seqtemp = string(newPathName)+
                       string("/")+
                       string(newActionName)+
	      	           string("/")+
				       string(newActionName)+
                       string(".seq");
      seqName = 	&seqtemp[0];

        string wavetemp = string(newPathName)+
                          string("/")+
                          string(newActionName)+
		                  string("/")+
		                  string(newActionName)+
                          string(".wav");
        waveName = &wavetemp[0];
}

DragonActionRecord::~DragonActionRecord()
{
    //dtor
}

void DragonActionRecord::print()
{
 cout<<"DragonActionRecord: pathName=  "<<pathName<<endl;
 cout<<"DragonActionRecord: actionName= \'"<<actionName<<"\'"<<endl;
 cout<<"DragonActionRecord: seqName=   "<<seqName<<endl;
 cout<<"DragonActionRecord: waveName=  "<<waveName<<endl;

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
