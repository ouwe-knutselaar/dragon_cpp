#include "DragonFileManager.h"



int main()
{
 DragonFileManager dfm;

 dfm.setCurrentPath("/var/dragon/actions");
 dfm.loadActionNamesList();

 dfm.defineRandomAction(1);

 dfm.defineRandomAction(1);
 dfm.defineRandomAction(1);
 dfm.defineRandomAction(1);
 dfm.defineRandomAction(1);
}
