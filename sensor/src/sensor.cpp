#include <cstdio>
#include <pigpio.h>

#define leftsensor 22
#define rightsensor 23
class infrared
{
public:
        void infrared()
        {
        	gpioSetMode(leftsensor,PI_INPUT);
        	gpioSetMode(rightsensor,PI_INPUT);
        	gpioSetPullUpDown(leftsensor, PI_PUD_UP);
        	gpioSetPullUpDown(rightsensor, PI_PUD_UP);
        }
        int readleft()
        {
        	return gpioRead(leftsensor);
        }
        int readright()
        {
        	return gpioRead(rightsensor);        
        }
	
};
