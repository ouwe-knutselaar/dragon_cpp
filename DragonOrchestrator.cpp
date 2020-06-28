#include "DragonOrchestrator.h"
#include "DragonEvent.h"
#include "DragonFileManager.h"
#include "DragonI2c.h"
#include "DragonTimer.h"
#include "DragonAudio.h"
#include "dynamicarray.h"

#include <iostream>
#include <string>
#include <fstream>



DragonFileManager dragonFileManager;
DragonI2c dragonI2c;
DragonTimer dragonTimer;
DragonAudio dragonAudio;



DragonOrchestrator::DragonOrchestrator()
{
	std::cout<<"DragonOrchestrator: Start DragonOrchestrator"<<endl;
}

DragonOrchestrator::~DragonOrchestrator()
{

}


void DragonOrchestrator::initialize()
{
    dragonFileManager.setCurrentPath("/home/gebruiker/dev/dragon/actions");
    dragonFileManager.loadActionNamesList();

    dragonAudio.initialize();

    dragonTimer.addEvent(*this);
    dragonTimer.startTimer();

}

void DragonOrchestrator::sendEvent(char *msg,int source,int val2)
{
	//Timer event
	if(source == 1)handleTimerEvent();
}

void DragonOrchestrator::handleTimerEvent()
{
	if(actionRunning == false)selectNewAction();
	executeNextActionInTheSequence();
}


void DragonOrchestrator::selectNewAction()
{
	std::cerr<<"DragonOrchestrator: select new action"<<endl;
	dragonFileManager.defineRandomAction(0);

	actionRunning = true;
	currentStep = 0;
	std::cerr<<"DragonOrchestrator: action has "<<stepListSize<<" steps"<<endl;

	// load the sequence file
	fstream sequenceFileHandle;
	sequenceFileHandle.open(dragonFileManager.getCurrentSequenceFile(), ios::in);
	string lineWithServoValues;
	while(getline(sequenceFileHandle, lineWithServoValues)){  //read data from file object and put it into string.
	         std::cerr << lineWithServoValues << "\n";   //print the data of the string
	         DragonActionLine newActionLine;

	      }

	dragonAudio.playWaveFile(&dragonFileManager.getCurrentWaveFile()[0]);

}


void DragonOrchestrator::executeNextActionInTheSequence()
{
	currentStep++;
	if(currentStep>stepListSize)
	{
		actionRunning = false;
	}
}
