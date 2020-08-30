#include "keylogger.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

keylogger::keylogger()
{
  cerr<<"keylogger: creat ekeylogger object\n";
}

keylogger::~keylogger()
{
}


void keylogger::startLogging()
{
  char* inputDevice="/dev/input/mice\0";
  miceEvent=open(inputDevice,O_RDONLY);
  fcntl(miceEvent,F_SETFL, O_NONBLOCK);
  thread keyLogThread(&keylogger::keyThread,this);
  keyLogThread.detach();
}


void keylogger::keyThread()
{
  cerr<<"keylogger: Start the log thread()\n";	
  char event[3];
  int readBytes;
  while(isRunning)
  {
    readBytes=read(miceEvent,event,3);
    if(readBytes==3)
     {
      printf("value:%d %d %d\n",event[0],event[1],event[2]);
      if(event[0]==8 && event[1]==0 && event[2]!=0)lastEvent=UP;   	// UP
      if(event[0]==40 && event[1]==0)lastEvent=DOWN;			// DOWN
      if(event[0]==24 && event[2]==0)lastEvent=LEFT;			// LEFT
      if(event[0]==8 && event[1]!=0 && event[2]==0)lastEvent=RIGHT;	// RIGHT
      if(event[0]==9 && event[1]==0 && event[2]==0)lastEvent=OKE;	// OKE
      if(event[0]==10 && event[1]==0 && event[2]==0)lastEvent=RETURN;	// RETURN
     }
     
  }
}


int keylogger::getLastKey()
{
  cerr<<"keylogger: Last key is "<<lastEvent<<"\n";
  int lastkey=lastEvent;
  lastEvent=NONE;
  return lastkey;  
}



