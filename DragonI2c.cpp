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
  if(gpioInitialise() < 0)
  {
    std::cerr<<"DragonI2C: Cannot open the PCA9865\n";
    return ;
  }

  handle = i2cOpen(1,0x40,0);
  std::cerr<<"DragonI2c: PCA9865 is open at "<<handle<<"\n";
}



void DragonI2c::setFrequency(int frequency)
{
 std::cerr<<"DragonI2C: Set PWM on "<<frequency<<" Hz\n";

 // Set the settings for the sequence
 int settings = i2cReadByteData(handle,0x00);
 int sleep = settings | 0x10;
 int wake = settings & 0xEF;
 int restart = wake | 0x80;

// printf("tt %X %X %X %X\n",settings,sleep,wake,restart);

 std::cerr<<"DragonI2C: Let the PCA9865 sleep \n";
 i2cWriteByteData(handle,0x00,sleep);

 std::cerr<<"DragonI2C: Set the PWM frequency\n";
 float prescaleval = 25000000.0f;
 prescaleval /= 4096.0;
 prescaleval /= (float) 60;
 prescaleval -= 1.0;
 float prescale = floor(prescaleval +0.5);
 i2cWriteByteData(handle,0xFE,(int) floor(prescale)); // Set frequency

 std::cerr<<"DragonI2C: Awake the PCA9865\n";
 i2cWriteByteData(handle,0x00,wake);

 // minimal 5uS sleep
 usleep(100000);

 // Restart to activate the new frequency
 i2cWriteByteData(handle,0x00,restart);

 int rc = i2cReadByteData(handle,0xFE);
 std::cerr<<"DragonI2c: Frequency set at "<<rc<<"\n";
}

void DragonI2c::setServoPosition(int servo,int position)
{
  if(servo < 0) return;
  if(servo > 15) return;
  if(position < 0) return;
  if(position > 4096) return;

  char led_l = (char) (( position & 0x0000FF00) >> 8);
  char led_h = (char) (( position & 0x000000FF) >> 0);

  i2cWriteByteData(handle,6 + (servo * 4),0x00);
  i2cWriteByteData(handle,7 + (servo * 4),0x00);
  i2cWriteByteData(handle,8 + (servo * 4),led_h);
  i2cWriteByteData(handle,9 + (servo * 4),led_l);

//  i2cWriteByteData(handle,0x12,0x00);
//  i2cWriteByteData(handle,0x13,0x00);
//  i2cWriteByteData(handle,0x14,led_h);
//  i2cWriteByteData(handle,0x15,led_l);

//  int rc = i2cReadByteData(handle,0x14);

//  printf("Servo %d at H: %d  L: %d  rc=%d handle=%d\n",6+(servo*4),led_h,led_l,rc,handle);
}

