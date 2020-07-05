#ifndef DRAGONACTIONRECORD_H
#define DRAGONACTIONRECORD_H

#include "dynamicarray.h"
#include <string>


using namespace std;

class DragonActionRecord
{
    public:
        DragonActionRecord(char *newPathName,        // name of the source path
                           char *newActionName      // name of the action
                           );
        virtual ~DragonActionRecord();
        void print();
        string getPathname();
        string getActionName();
        string getSeqName();
        string getWaveName();
        int getNumberOfSteps();
        int* getActionAt(int);

    protected:

    private:
        string pathName;        		// name of the source path
        string actionName;      		// name of the action
        string seqName;         		// name of the sequence file
        string waveName;        		// name of the wave file
        DragonActionLine *sequence;		// Sequence of the dragon
        int numberOfSteps;

};

#endif // DRAGONACTIONRECORD_H
