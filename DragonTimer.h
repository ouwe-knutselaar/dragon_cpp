#ifndef DRAGONTIMER_H
#define DRAGONTIMER_H

#include <string>
#include "DragonEvent.h"

using namespace std;


class DragonTimer
{
    public:
		DragonTimer();
        virtual ~DragonTimer();
        void addEvent(DragonEvent &evt);
        void startTimer();

    protected:

    private:
        DragonEvent *callBackObject;
        const int intervalInMilliseconds = 50;		// Default interval = 50mS
        void threadFunction();
        bool running = true;
};

#endif // DRAGONTIMER_H
