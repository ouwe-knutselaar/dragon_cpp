#ifndef KEYLOGGER_H
#define KEYLOGGER_H


class keylogger
{

 public:
   keylogger();
   virtual ~keylogger();
   void startLogging();
   int getLastKey();
   enum keys{NONE=0,UP=1,DOWN=2,LEFT=3,RIGHT=4,OKE=5,RETURN=6};

 private:  
   void keyThread();
   int miceEvent;
   bool isRunning = true;
   keys lastEvent;
};

#endif
