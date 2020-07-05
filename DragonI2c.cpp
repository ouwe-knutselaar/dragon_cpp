#include "DragonI2c.h"
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <iostream>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port




DragonI2c::DragonI2c()
{
	std::cerr<<"DragonI2c: Starting DragonI2c"<<std::endl;
	initialize();
}


DragonI2c::~DragonI2c(){
}


void DragonI2c::initialize()
{
    int i2c_dev = open ("/dev/i2c-1", O_RDWR);
    if(i2c_dev < 0)
    {
    	std::cerr<<"\x1B[31mDragonI2c: Cannot op the I2C port \033[0m\n";
    	return;
    }

    int i2c_addr = 0x40;
    int rc = ioctl(i2c_dev, I2C_SLAVE, i2c_addr);
    if(rc < 0)
    {
    	std::cerr<<"\x1B[31mDragonI2c: Failed to acquire bus access and/or talk to slave.\033[0m\n";
    	return;
    }


    std::cerr<<"DragonI2c: I2C initialized"<<std::endl;
    buf[0] = MODE1;
}

void DragonI2c::send_msg(unsigned int *servoValues)
{
	//std::cerr<<servoValues[0]<<" "<<servoValues[1]<<std::endl;
}


