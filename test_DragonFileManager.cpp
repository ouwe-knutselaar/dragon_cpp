#include "DragonFileManager.h"
#include <iostream>

using namespace std;


int main()
{
 DragonFileManager dfm;

 dfm.setCurrentPath("/var/dragon/actions");
 dfm.loadActionNamesList();

 for(int tel=0;tel<5;tel++)
 {
 	dfm.defineRandomAction(1);
	cout<<"steps "<<dfm.getCurrentSequenceSteps()<<endl;
	for(int count=0; count<dfm.getCurrentSequenceSteps();count++)
	{
		cout<<dfm.getCurrentActionServoSteps(count)->getServoValues()[1]<<" ";
	}
 }
}
