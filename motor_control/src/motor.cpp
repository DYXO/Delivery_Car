#include <cstdio>
#include <pigpio.h>

#define leftmotor1 17
#define leftmotor2 25
#define rightmotor1 18
#define rightmotor2 24
#define leftsensor 23
#define rightsensor 22
class motor
{
public:
	void SetMotor(int Lspeed,int Rspeed)
	{
		if(Lspeed>255||Rspeed>255||Lspeed<-255||Rspeed<-255)
		{
			printf("erro!\n");
			return;
		}
		else
		{
			if(Lspeed>=0)
			{
				gpioPWM(leftmotor1, Lspeed);
				gpioPWM(leftmotor2, 0);
			}
			else if(Lspeed<0)
			{
				Lspeed=-Lspeed;
				gpioPWM(leftmotor1, 0);
				gpioPWM(leftmotor2, Lspeed);
			}
			if(Rspeed>=0)
			{
				gpioPWM(rightmotor1, Rspeed);
				gpioPWM(rightmotor2, 0);
			}
			else if(Rspeed<0)
			{
				Rspeed=-Rspeed;
				gpioPWM(rightmotor1, 0);
				gpioPWM(rightmotor2, Rspeed);
			}
		}
		return;
	}
};

class infrared
{
public:
        infrared()
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

int main(int argc, char ** argv)
{
  	(void) argc;
  	(void) argv;
  	while(gpioInitialise() < 0);
  	motor DeliveryRobot_motor;
  	infrared DeliveryRobot_Sensor;
	while(1)
	{
		if(DeliveryRobot_Sensor.readleft()==0&&DeliveryRobot_Sensor.readright()==0)
		{
		DeliveryRobot_motor.SetMotor(-140,-140);
		}
		else if(DeliveryRobot_Sensor.readleft()==0&&DeliveryRobot_Sensor.readright()==1)
		{
		DeliveryRobot_motor.SetMotor(-100,200);
		}
		else if(DeliveryRobot_Sensor.readleft()==1&&DeliveryRobot_Sensor.readright()==0)
		{
		DeliveryRobot_motor.SetMotor(200,-100);
		}		
		else if(DeliveryRobot_Sensor.readleft()==1&&DeliveryRobot_Sensor.readright()==1)
		{
		DeliveryRobot_motor.SetMotor(0,0);
		}
		//gpioSleep(PI_TIME_RELATIVE,0,10000);
	}
	printf("hello world my_package package\n"); 
	return 0;	
}

