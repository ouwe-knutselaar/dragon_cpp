#include <iostream>
#include <unistd.h>
#include "DragonFileManager.h"
#include "DragonOrchestrator.h"


using namespace std;


int main()
{
    cout<<"dragon_cpp: Start the Dragon C++ based\n";

    DragonOrchestrator dragonOrchestrator;
    dragonOrchestrator.initialize();

    // Main loop
    while(true)
    {
    	sleep(1);
    }

    return 0;
}
