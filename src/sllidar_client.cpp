#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <math.h>
#include <pigpio.h>
#define RAD2DEG(x) ((x)*180./M_PI)
#define leftmotor1 17
#define leftmotor2 25
#define rightmotor1 18
#define rightmotor2 24

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
				printf("test\n");
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

motor avoidance_motor;
int frontclear=0;
int leftclear=0;
int rightclear=0;
int turnleft_flag=0;
static void scanCb(sensor_msgs::msg::LaserScan::SharedPtr scan) {
  int count = scan->scan_time / scan->time_increment;
  printf("[SLLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
  printf("[SLLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min),
         RAD2DEG(scan->angle_max));
  frontclear=1;
  leftclear=1;
  rightclear=1;
  for (int i = 0; i < count; i++) 
  {
    float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
    if(scan->ranges[i]<0.3&&scan->ranges[i]>0.1)
    {
    if(-30<degree&&degree<30)
    {
    	printf("[SLLIDAR INFO]: angle-distance : [%f, %f]\n", degree, scan->ranges[i]);
	frontclear=0;
    }
    if(-140<degree&&degree<-50)
    {
    	leftclear=0;
    }
    if(50<degree&&degree<140)
    {
    	rightclear=0;
    }
    }
  }
  if(frontclear==1)avoidance_motor.SetMotor(160,160);
  /*else if(leftclear==1)avoidance_motor.SetMotor(-160,160);
  else if(rightclear==1)avoidance_motor.SetMotor(160,-160);*/
  else avoidance_motor.SetMotor(-160,160);
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  while(gpioInitialise() < 0)
  {printf("erro\n");}
  
  auto node = rclcpp::Node::make_shared("sllidar_client");

  auto lidar_info_sub = node->create_subscription<sensor_msgs::msg::LaserScan>(
                        "scan", rclcpp::SensorDataQoS(), scanCb);

  rclcpp::spin(node);

  rclcpp::shutdown();


  return 0;
}
