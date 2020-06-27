#include "DragonTimer.h"
#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>


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
	struct timeval trgtime,timenow;
	gettimeofday(&trgtime, NULL);
	long int interval_triggertime = trgtime.tv_sec * 1000000 + trgtime.tv_usec;
	long int epoch_in_ms=0;

	interval_triggertime = interval_triggertime + 20000;
	while(running_)
	{
		usleep(1000);
		int rc=gettimeofday(&timenow, NULL);
		if(rc!=0)cout<<" error";
		epoch_in_ms = timenow.tv_sec * 1000000 + timenow.tv_usec;
		if(epoch_in_ms > interval_triggertime)
			{callBackObject_->sendEvent("timer",1,2);
			interval_triggertime = interval_triggertime + 20000;	// add 20 ms
			 cout<<".";
			}
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
	callBackObject_ = &evt;
}


