#ifndef DRAGONFILEMANAGER_H
#define DRAGONFILEMANAGER_H

#include <string>
#include <vector>

#include "DragonActionRecord.h"

using namespace std;

class DragonFileManager
{
    public:
        DragonFileManager();
        virtual ~DragonFileManager();

        void loadActionNamesList();
        void setCurrentPath(char*);
        void getCurrentActionSteps(unsigned int**,int*);
        void defineRandomAction(int actionType);
        string getCurrectWaveFile();


    protected:

    private:
        vector<DragonActionRecord> dirList_;		// The list with actions
        char* currentpath_;							// Data path for the action
        int currentAction_;							// number of the current action
        unsigned int* seqLineToIntPtr(string);

};

#endif // DRAGONFILEMANAGER_H
