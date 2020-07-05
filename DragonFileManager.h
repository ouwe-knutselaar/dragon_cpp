#ifndef DRAGONFILEMANAGER_H
#define DRAGONFILEMANAGER_H


#include <vector>

#include "DragonActionRecord.h"
#include <string>



class DragonFileManager
{
    public:
        DragonFileManager();
        virtual ~DragonFileManager();

        void loadActionNamesList();
        void setCurrentPath(char*);
        void defineRandomAction(int actionType);
        int getCurrentSequenceSteps();
        string getCurrentWaveFile();
        string getCurrentSequenceFile();
        int* getCurrentActionServoSteps(int);


    protected:

    private:
        vector<DragonActionRecord> dirList_;		// The list with actions
        char* currentpath_;							// Data path for the action
        int currentAction_;							// number of the current action
        unsigned int* seqLineToIntPtr(string);

};

#endif // DRAGONFILEMANAGER_H
