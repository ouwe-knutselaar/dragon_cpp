#include "DragonI2c.h"
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <iostream>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port




DragonI2c::DragonI2c()
{
	std::cout<<"DragonI2c: Starting DragonI2c"<<std::endl;
}


DragonI2c::~DragonI2c()
{
    //dtor
}


void DragonI2c::initialize()
{
    unsigned char buffer[16];
    int i2c_dev = open ("/dev/i2c-1", O_RDWR);
    std::cout<<"DragonI2c: Open I2C result is "<<i2c_dev<<std::endl;
    int i2c_addr = 0x40;

    int rc = ioctl(i2c_dev, I2C_SLAVE, i2c_addr);

    buf[0] = MODE1;
}

void DragonI2c::send_msg(unsigned int[16])
{

}
