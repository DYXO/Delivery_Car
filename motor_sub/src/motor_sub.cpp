#include <memory>
#include <stdio.h>
#include <pigpio.h>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>

#define leftmotor1 17
#define leftmotor2 25
#define rightmotor1 18
#define rightmotor2 24

using std::placeholders::_1;
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
motor KeyCtrlMotor;
class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      "cmd_vel", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const geometry_msgs::msg::Twist & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard:%f,%f,%f",msg.linear.x,msg.linear.y,msg.linear.z);
      if(msg.linear.x==0.5)
      {
      	printf("forward\n");
	KeyCtrlMotor.SetMotor(200,200);
      }
      else
        {
          if(msg.linear.y==0.5)
          {
            printf("turnleft\n");
	    KeyCtrlMotor.SetMotor(-200,200);
          }
          else if(msg.linear.y==-0.5)
          {
            printf("turnright\n");
            KeyCtrlMotor.SetMotor(200,-200);
          }
          else
          {
            printf("stop\n");
            KeyCtrlMotor.SetMotor(0,0);
          }
        }
    }
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  while(gpioInitialise() < 0)
  {printf("erro\n");}
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
