#define L_MOTOR_INT 2 
#define R_MOTOR_INT 3

// 2pi = 980 triggered times
const double rot_per_count = 2*M_PI/980;

void setup() {
  // put your setup code here, to run once:
  pinMode(L_MOTOR_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(L_MOTOR_INT), left_int, RISING);
  attachInterrupt(digitalPinToInterrupt(R_MOTOR_INT), right_int, RISING);
  Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void left_int(){
  static unsigned long prev_time = 0, curr_time = 0;
  double left_speed_fb = 0;
  curr_time = micros();
  //Serial.println("Left int");
  //Serial.print("time = ");
  //Serial.println(curr_time);
  if(prev_time == 0){
    prev_time = curr_time;
    return;
  }
  left_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
  Serial.println(left_speed_fb);
  prev_time = curr_time;
}

void right_int(){
  static unsigned long prev_time = 0, curr_time = 0;
  double right_speed_fb = 0;
  curr_time = micros();
  //Serial.println("Left int");
  //Serial.print("time = ");
  //Serial.println(curr_time);
  if(prev_time == 0){
    prev_time = curr_time;
    return;
  }
  right_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
  Serial.println(right_speed_fb);
  prev_time = curr_time;
}
