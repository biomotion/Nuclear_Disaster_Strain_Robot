#define L_MOTOR_INT 2 
#define R_MOTOR_INT 3
void setup() {
  // put your setup code here, to run once:
  pinMode(L_MOTOR_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(L_MOTOR_INT), left_int, RISING);
    Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void left_int(){
  static unsigned long enter_time=0;
  enter_time++;
  Serial.println(enter_time);
}
