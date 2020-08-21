#ifndef DRAGONI2C_H
#define DRAGONI2C_H


class DragonI2c
{
    public:
        DragonI2c();
        virtual ~DragonI2c();
        void initialize();
        void setFrequency(int);
        void setServoPosition(int,int);
        
	void sendByte(int,char);
    protected:

    private:
       int PCAADDR = 0x40;
       int MODE1 = 0x00;
       int MODE2 = 0x01;
       int PRESCALE = 0xFE;
       int SLEEP = 0b00010000;
       int AWAKE = 0b11101111;
       int AI = 0b00100000;
       int RESTART = 0b10000000;
       int LEDBASE = 0x06;
       int LEDBASELIST[16] = { 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 66 };
       char buf[60];
       int handle;		// File handler for the PCA9865

};

#endif // DRAGONI2C_H
