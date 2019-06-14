// value range:
// v = -5 ~ 5
// omega = -5 ~ 5

#include <ros.h>
#include <duckietown_msgs/Twist2DStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#define L1 5
#define L2 6
#define R1 9
#define R2 10


ros::NodeHandle nh;

void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg);
void set_car_speed(float _v, float _omega);
//std_msgs::String str_msg;

//Publishers and Subscribers
ros::Subscriber<duckietown_msgs::Twist2DStamped> sub_car_cmd("car_cmd", car_cmd_cb );
//ros::Publisher chatter("chatter", &str_msg);

float v, omega;
bool state;

void setup() {
  pinMode(13, OUTPUT);
  
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub_car_cmd);
//  nh.advertise(chatter);
  v = 0;
  omega = 0;
  state = true;
}

void loop() {
//  set_car_speed(v, omega);
//  str_msg.data = "spin";
//  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(33);
}

void car_cmd_cb(const duckietown_msgs::Twist2DStamped& msg){

//  String data ="v= ";
  if(state){
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  state = !state;
  v = msg.v;
  omega = msg.omega;
  set_car_speed(v, omega);
//  data = data + v + "omega = " + omega;
  
//  str_msg.data = data.c_str();
//  chatter.publish( &str_msg );
}

void set_car_speed(float _v, float _omega){
  int16_t r_speed, l_speed;
  l_speed = 255*(_v - _omega)/10;
  r_speed = 255*(_v + _omega)/10;

  if(l_speed > 0){
    analogWrite(L1, l_speed);
    analogWrite(L2, 0);
  }else{
    analogWrite(L1, 0);
    analogWrite(L2, -l_speed);
  }

  if(r_speed > 0){
    analogWrite(R1, r_speed);
    analogWrite(R2, 0);
  }else{
    analogWrite(R1, 0);
    analogWrite(R2, -r_speed);
  }

}
