#include <ros.h>
#include <duckietown_msgs/Twist2DStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg);
void set_car_speed(float _v, float _omega);

//
ros::Subscriber<std_msgs::Empty> sub_car_cmd("car_cmd_cb", car_cmd_cb );

float v, omega;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub_car_cmd);
  v = 0;
  omega = 0;
}

void loop() {
  set_car_speed(v, omega);
  nh.spinOnce();
  delay(33);
}

void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg){
  digitalWrite(13, HIGH-digitalRead(13));
  float _v = msg.v;
  float _omega = msg.omega;
}

void set_car_speed(float _v, float _omega){
  
}
