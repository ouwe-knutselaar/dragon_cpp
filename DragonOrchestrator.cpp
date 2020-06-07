#include "DragonOrchestrator.h"
#include "DragonEvent.h"
#include "DragonFileManager.h"
#include "DragonI2c.h"
#include "DragonTimer.h"

#include <iostream>
#include <string>

using namespace std;

DragonFileManager dragonFileManager;
DragonI2c dragonI2c;
DragonTimer dragonTimer;



DragonOrchestrator::DragonOrchestrator()
{
    cout<<"DragonOrchestrator: Start DragonOrchestrator"<<endl;
}

DragonOrchestrator::~DragonOrchestrator()
{
    //dtor
}


void DragonOrchestrator::initialize()
{
    dragonFileManager.setCurrentPath("/home/gebruiker/dev/dragon/actions");
    dragonFileManager.loadActionNamesList();

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
	cout<<"DragonOrchestrator: select new action"<<endl;
	dragonFileManager.loadAction("the_devil",stepList,&stepListSize);
	actionRunning = true;
	currentStep = 0;
	cout<<"DragonOrchestrator: action has "<<stepListSize<<" steps"<<endl;
}


void DragonOrchestrator::executeNextActionInTheSequence()
{
	unsigned int *temp = stepList[currentStep];
	// to-do send ti I2C

	cout<<currentStep<<" ";
	currentStep++;
	if(currentStep>stepListSize)
	{
		cout<<endl;
		actionRunning = false;
	}
}
