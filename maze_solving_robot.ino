#include "motors.h"
#include "sensors.h"

float Kp=2.2,Ki=0,Kd=0;
double error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int initial_motor_speed=200;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,HIGH);
  digitalWrite(13,LOW);
  initializeMotor();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
 moveStraight();
 readSensor();
 if((sensorValues[0] >200) && (sensorValues[1] >200) &&(sensorValues[2] >200) &&(sensorValues[3] >200) &&(sensorValues[4] >200)){
   moveLeftMotor(0);
   moveRightMotor(0);
   delay(2000);
 }
 
}

void moveStraight(){
  calculate_pid();
 motor_control();
}
void calculate_pid()
{   int position = readLine();
    error = position-BASEPOSITION;
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = ((Kp*P) + (Ki*I) + (Kd*D))/20;
    
    previous_I=I;
    previous_error=error;
}


void motor_control(){
  //Calculate the effective motor speed
  int leftSpeed = initial_motor_speed+PID_value;
  int rightSpeed = initial_motor_speed-PID_value;
  //THe motor speed shouldnot exceed max PWM
  leftSpeed = constrain(leftSpeed,0,255);
  rightSpeed = constrain(rightSpeed,0,255);

  moveLeftMotor(leftSpeed);
  moveRightMotor(rightSpeed);
  
}














