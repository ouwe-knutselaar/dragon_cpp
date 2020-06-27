#ifndef DRAGONACTIONRECORD_H
#define DRAGONACTIONRECORD_H

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

    protected:

    private:
        string pathName;        		// name of the source path
        string actionName;      		// name of the action
        string seqName;         		// name of the sequence file
        string waveName;        		// name of the wave file
        unsigned short int **sequence;	// Sequence of the dragon
};

#endif // DRAGONACTIONRECORD_H