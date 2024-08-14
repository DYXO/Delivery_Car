#include "playsound.h"
#include <pigpio.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
	soundplayer test("Sound.wav");
	test.play();
	//test.~soundplayer();
	/*while(!gpioInitialise())
	{
		printf("hhhh!\n");
	}*/
	return 0;
}
