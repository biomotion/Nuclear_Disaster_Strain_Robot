#include <ros.h>
#include <duckietown_msgs/Twist2DStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;

void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg);
std_msgs::String str_msg;
//
ros::Subscriber<duckietown_msgs::Twist2DStamped> sub_car_cmd("car_cmd_cb", car_cmd_cb);
ros::Publisher pub_string("arduino_out", &str_msg);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub_car_cmd);
  nh.advertise(pub_string);
}

void loop() {
  nh.spinOnce();
  delay(50);
}


void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg){
  digitalWrite(13, HIGH-digitalRead(13));
  float _v = msg.v;
  float _omega = msg.omega;
  str_msg.data = "car cmd recieved";
  pub_string.publish(&str_msg);
}
