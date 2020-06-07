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
        void loadAction(string,unsigned int**,int*);

    protected:

    private:
        vector<DragonActionRecord> __dirList;
        char* __currentpath;
        unsigned int* seqLineToIntPtr(string);

};

#endif // DRAGONFILEMANAGER_H
