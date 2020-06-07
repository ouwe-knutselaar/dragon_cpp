#include "DragonTimer.h"
#include <thread>
#include <iostream>
#include <unistd.h>


using namespace std;


DragonTimer::DragonTimer()
{
    cout<<"DragonTimer: Start DragonTimer";
}

DragonTimer::~DragonTimer()
{
    //dtor
}

void DragonTimer::threadFunction()
{
	cout<<"DragonTimer: Start the timer thread function"<<endl;
	while(running)
	{
		usleep(5000);
		callBackObject->sendEvent("timer",1,2);
	}
}


void DragonTimer::startTimer()
{
	cout<<"DragonTimer: Start the timer Thread"<<endl;
	thread timerThread(&DragonTimer::threadFunction,this);
	timerThread.detach();
}


void DragonTimer::addEvent(DragonEvent &evt)
{
	callBackObject = &evt;
}



