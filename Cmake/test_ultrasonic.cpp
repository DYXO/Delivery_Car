#include "motor.h"
#include "ultrasonic.h"

class PrintDistanceCallback:public UltrasonicCallback
{
	virtual void distance_ready(float d) 
	{
		printf("%f\n",d);
	}
};

int main(int argc, char *argv[]) 
{

	while(1)
	{

	}
	return 0;
}
