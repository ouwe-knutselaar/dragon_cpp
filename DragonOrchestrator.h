#ifndef DRAGONORCHESTRATOR_H
#define DRAGONORCHESTRATOR_H


#include "DragonFileManager.h"
#include "DragonI2c.h"
#include "DragonEvent.h"
#include "dynamicarray.h"




class DragonOrchestrator:public DragonEvent
{
    public:
        DragonOrchestrator();
        virtual ~DragonOrchestrator();
        void initialize();
        void sendEvent(char*,int,int);
    protected:

    private:
        void handleTimerEvent();
        void selectNewAction();
        void executeNextActionInTheSequence();

        bool actionRunning = false;		// Flag if a sequence is running
        dynamicarray stepList;		// reference to the sequence list

        int stepListSize;
        int currentStep = 0;				// Step in the sequence list
};

#endif // DRAGONORCHESTRATOR_H
