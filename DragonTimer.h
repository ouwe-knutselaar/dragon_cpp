#ifndef DRAGONTIMER_H
#define DRAGONTIMER_H

#include <string>
#include "DragonEvent.h"




class DragonTimer
{
    public:
		DragonTimer();
        virtual ~DragonTimer();
        void addEvent(DragonEvent &evt);
        void startTimer();

    protected:

    private:
        DragonEvent *callBackObject_;
        const int intervalInMilliseconds_ = 20;		// Default interval = 50mS
        void threadFunction();
        bool running_ = true;
        int intervalInUsec = 20000;	//org
        //int intervalInUsec = 2000;
};

#endif // DRAGONTIMER_H
