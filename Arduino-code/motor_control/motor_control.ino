#define L_MOTOR_INT 2 
#define R_MOTOR_INT 3
#define L_MOTOR_PIN1 9
#define L_MOTOR_PIN2 10
#define R_MOTOR_PIN1 5
#define R_MOTOR_PIN2 6

// 2pi = 980 triggered times
const double rot_per_count = 2*M_PI/980;
double left_speed_fb=0, right_speed_fb=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(L_MOTOR_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(L_MOTOR_INT), left_int, RISING);
  attachInterrupt(digitalPinToInterrupt(R_MOTOR_INT), right_int, RISING);

  pinMode(L_MOTOR_PIN1, OUTPUT);
  pinMode(L_MOTOR_PIN2, OUTPUT);
  pinMode(R_MOTOR_PIN1, OUTPUT);
  pinMode(R_MOTOR_PIN2, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  set_left_speed(0);
  delay(2000);
  set_left_speed(10.0);
  delay(2000);

}

void set_left_speed(double target_speed){
  while(1){
    static double duty = 0;
    const double gain = 0.2;
    double speed_diff = target_speed - left_speed_fb;
    if(speed_diff > -0.05 && speed_diff < 0.05) return;
    Serial.print("duty cycle: ");
    Serial.print(duty);
    Serial.print(" speed: ");
    Serial.print(left_speed_fb);
    Serial.print(" speed diff: ");
    Serial.print(speed_diff);
    Serial.println();
    duty += speed_diff * gain;
    analogWrite(L_MOTOR_PIN1, duty);
    
  }
}

void left_int(){
  static unsigned long prev_time = 0, curr_time = 0;
  curr_time = micros();
  //Serial.println("Left int");
  //Serial.print("time = ");
  //Serial.println(curr_time);
  if(prev_time == 0){
    prev_time = curr_time;
    return;
  }
  left_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
  //Serial.println(left_speed_fb);
  prev_time = curr_time;
}

void right_int(){
  static unsigned long prev_time = 0, curr_time = 0;
  curr_time = micros();
  //Serial.println("Left int");
  //Serial.print("time = ");
  //Serial.println(curr_time);
  if(prev_time == 0){
    prev_time = curr_time;
    return;
  }
  right_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
  //Serial.println(right_speed_fb);
  prev_time = curr_time;
}
