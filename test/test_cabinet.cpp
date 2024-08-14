#include "cabinet.h"

int main(int argc, char *argv[]) 
{
	scanner s1(16);
	cabinet DeliveryBox(&s1);
	DeliveryBox.deposit();
	DeliveryBox.takeout();
	/*time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	time_sleep(1);
	printf("5s\n");
	DeliveryBox.takeout();*/
	while(1)
	{
	}
	return 0;
}
