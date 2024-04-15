#include <cstdio>
#include <pigpio.h>

#define leftmotor 17
#define rightmotor 18
class motor
{
public:
        void forward(int speed)
	{
		gpioPWM(leftmotor, speed);
		gpioPWM(rightmotor,speed);		
	}
	void turnleft(int left_speed,int right_speed)
	{
		gpioPWM(leftmotor, left_speed);
		gpioPWM(rightmotor,right_speed);
	}
	void turnright(int left_speed,int right_speed)
	{
		gpioPWM(leftmotor, left_speed);
		gpioPWM(rightmotor,right_speed);
	}
	
};

int main(int argc, char ** argv)
{
  	(void) argc;
  	(void) argv;
  	motor DeliveryRobot_motor;
  	
	while(gpioInitialise() < 0);
	while(1)
	{
		
		DeliveryRobot_motor.turnleft(100,255);
		
		gpioSleep(PI_TIME_RELATIVE, 1, 0);

		DeliveryRobot_motor.turnright(0,0);
		
		gpioSleep(PI_TIME_RELATIVE, 1, 0);
	}
	printf("hello world my_package package\n"); 
	return 0;	
}

