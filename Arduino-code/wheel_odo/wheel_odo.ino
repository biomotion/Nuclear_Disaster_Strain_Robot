#define L_MOTOR_INT 2 
#define R_MOTOR_INT 3
#define DIR_L 7
#define DIR_R 8
#define HZ 100 //updating rate

#define RADIUS 0.032 // Wheel radius, in meter
#define CPR 980.0   // Encoder Counts Per Revolution
#define WIDTH 0.167 // Two wheel distance, in meter

// 2pi = 980 triggered times
const double rot_per_count = 2*M_PI/CPR;
int32_t l_count, r_count;

void setup() {
  pinMode(L_MOTOR_INT, INPUT);
  pinMode(R_MOTOR_INT, INPUT);
  pinMode(DIR_L, INPUT);
  pinMode(DIR_R, INPUT);

  l_count = 0;
  r_count = 0;

  
  attachInterrupt(digitalPinToInterrupt(L_MOTOR_INT), left_int, RISING);
  attachInterrupt(digitalPinToInterrupt(R_MOTOR_INT), right_int, RISING);
  Serial.begin(57600);
  Serial.println("Start");
}

void loop() {
  static unsigned long nextTime = millis();
  if(millis() > nextTime){
    Serial.print("time: ");
    Serial.println(millis());
    nextTime += 1000/HZ;

    
    Serial.print("l: ");
    Serial.print(l_count);
    Serial.print(", r: ");
    Serial.println(r_count);
  }

}

void left_int(){
//  static unsigned long prev_time = 0, curr_time = 0;
//  double left_speed_fb = 0;
//  curr_time = micros();
//
//  if(prev_time == 0){
//    prev_time = curr_time;
//    return;
//  }
//  left_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
//  Serial.println(left_speed_fb);
//  prev_time = curr_time;

  if(digitalRead(DIR_L) == HIGH) l_count--;
  else l_count++;

//  Serial.println(l_count);
}

void right_int(){
//  static unsigned long prev_time = 0, curr_time = 0;
//  double right_speed_fb = 0;
//  curr_time = micros();
//
//  if(prev_time == 0){
//    prev_time = curr_time;
//    return;
//  }
//  right_speed_fb = rot_per_count * 1e6 / (curr_time - prev_time);
//  Serial.println(right_speed_fb);
//  prev_time = curr_time;
  if(digitalRead(DIR_R) == HIGH) r_count--;
  else r_count++;

//  Serial.println(r_count);
}
