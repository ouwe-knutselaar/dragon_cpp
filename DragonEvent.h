#ifndef DRAGONEVENT_H
#define DRAGONEVENT_H

#include <string>

// Event 1 = timerevent

class DragonEvent
{
    public:
        DragonEvent();
        virtual ~DragonEvent();
        virtual void sendEvent(char *msg,int source,int val){};

    protected:

    private:
};

#endif // DRAGONEVENT_H
