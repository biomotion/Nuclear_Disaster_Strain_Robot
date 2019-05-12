#define L_MOTOR_INT 2 
#define R_MOTOR_INT 3

void setup() {
  // put your setup code here, to run once:
  pinMode(L_MOTOR_INT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(L_MOTOR_INT), left_int, RISING);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void left_int(){
  Serial.println("Left int");
}
