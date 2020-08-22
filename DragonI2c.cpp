#include "DragonI2c.h"
#include <pigpio.h>
#include <iostream>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <math.h>
#include <stdio.h>


DragonI2c::DragonI2c()
{
  std::cerr<<"DragonI2c: Starting DragonI2c"<<std::endl;
}


DragonI2c::~DragonI2c(){
}


void DragonI2c::initialize()
{
  std::cerr<<"DragonI2C: Open the PCA9865\n";
  int rc = gpioInitialise();
  if(rc < 0)
  {
    std::cerr<<"DragonI2C: Cannot open the PCA9865 with error "<<rc<<" \n";
    return ;
  }
  std::cerr<<"DragonI2c: gpio Initialized rc="<<rc<<"\n";

  handle = i2cOpen(1,0x40,0);
  std::cerr<<"DragonI2c: PCA9865 is open at "<<handle<<"\n";

  std::cerr<<"DragonI2c: Reset the PCA9865\n";
  sendByte(0x00,0x00);
  sendByte(0x01,0x04);
}



void DragonI2c::setFrequency()
{

 // Set the settings for the sequence
 int settings = i2cReadByteData(handle,0x00);
 int sleep = settings | 0x10;
 int wake = settings & 0xEF;
 int restart = wake | 0x80;

 std::cerr<<"DragonI2C: Let the PCA9865 sleep \n";
 //sendByte(0x00,sleep);
 sendByte(0x00,0x10);

 std::cerr<<"DragonI2C: Set the PWM frequency at 60Hz\n";
 sendByte(0xFE,PRESCALE); // Set frequency

 std::cerr<<"DragonI2C: Awake the PCA9865\n";
 //sendByte(0x00,wake);
 sendByte(0x00,0xA0);

 // minimal 5uS sleep
 usleep(100000);

 // Restart to activate the new frequency
 sendByte(0x01,0x04);

}

void DragonI2c::setServoPosition(int servo,int position)
{
  if(servo < 0) return;
  if(servo > 15) return;
  if(position < 0) return;
  if(position > 4096) return;

  char led_l = (char) (( position & 0x0000FF00) >> 8);
  char led_h = (char) (( position & 0x000000FF) >> 0);
  sendByte(6 + (servo * 4),0x00);
  sendByte(7 + (servo * 4),0x00);
  sendByte(8 + (servo * 4),led_h);
  sendByte(9 + (servo * 4),led_l);
}

void DragonI2c::sendByte(int addr, char byte)
{
	int rc = i2cWriteByteData(handle,addr,byte);
	if(rc != 0)
	{
          std::cerr<<"Error writing to "<<addr<<"with value "<<byte<<" rc="<<rc<<"\n";
	}
}
