#include "DragonOrchestrator.h"
#include "DragonEvent.h"
#include "DragonFileManager.h"
#include "DragonI2c.h"
#include "DragonTimer.h"
#include "DragonAudio.h"
#include "dynamicarray.h"
#include "keylogger.h"

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>



DragonFileManager dragonFileManager;
DragonI2c dragonI2c;
DragonTimer dragonTimer;
DragonAudio dragonAudio;
dynamicarray actionArrayForTheServos;
keylogger keylog;


DragonOrchestrator::DragonOrchestrator()
{
	std::cerr<<"DragonOrchestrator: Start DragonOrchestrator"<<endl;
}

DragonOrchestrator::~DragonOrchestrator()
{

}


void DragonOrchestrator::initialize()
{
    dragonFileManager.setCurrentPath("/var/dragon/actions");
    dragonFileManager.loadActionNamesList();

    keylog.startLogging();

    dragonTimer.addEvent(*this);
    dragonTimer.startTimer();

    dragonI2c.initialize();
    dragonI2c.setFrequency();
}


void DragonOrchestrator::sendEvent(char *msg,int source,int val2)
{
	//Timer event
	if(source == 1)handleTimerEvent();
}

void DragonOrchestrator::handleTimerEvent()
{
	if(actionRunning == false)selectNewAction();
	currentStep++;
	//std::cerr<<".";
	DragonActionLine *line = dragonFileManager.getCurrentActionServoSteps(currentStep);
	for(int tel=0;tel<15;tel++)
	{
		dragonI2c.setServoPosition(tel,line->getServoValues()[tel]);
	}
	if(currentStep>stepListSize)
	{
		actionRunning = false;
		std::cerr<<endl;;
	}
}


void DragonOrchestrator::selectNewAction()
{
	std::cerr<<"DragonOrchestrator: select new action"<<endl;
	dragonFileManager.defineRandomAction(0);
	std::cerr<<"DragonOrchestrator: new Action is "<<dragonFileManager.getCurrentSequenceFile()<<endl;
	actionArrayForTheServos.clear();

	actionRunning = true;
	currentStep = 0;
	stepListSize = dragonFileManager.getCurrentSequenceSteps();
	std::cerr<<"DragonOrchestrator: action has "<<stepListSize<<" steps"<<endl;

	dragonAudio.playWaveFile(&dragonFileManager.getCurrentWaveFile()[0]);
}



