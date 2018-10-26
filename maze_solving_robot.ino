#include "motors.h"
#include "sensors.h"

float Kp=2.2,Ki=0,Kd=0;
double error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int initial_motor_speed=200;
int sensorThreshold = 100;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,HIGH);
  digitalWrite(13,LOW);
  initializeMotor();
  
}

void loop() {
  // put your main code here, to run repeatedly:


 readSensor();
 if(sensorValues[0]<sensorThreshold && sensorValues[4]<sensorThreshold ){
  moveStraight();
 }else{
  readSensor();
  leftHandWall(); 
 }

 
}

void leftHandWall(){
  if(sensorValues[0]>sensorThreshold && sensorValues[4]>sensorThreshold){
    moveInch(1);
    readSensor();
    if(sensorValues[0]>sensorThreshold || sensorValues[4]>sensorThreshold){
      done();
    }
    if(sensorValues[0]<sensorThreshold && sensorValues[4]>sensorThreshold){
      turnLeft();
    }
  }

  if(sensorValues[4]>sensorThreshold){
    moveInch(1);
    readSensor();
    if(sensorValues[0]>sensorThreshold && sensorValues[4] > sensorThreshold){
      turnLeft(); 
    }else{
      done();
    }
  }

  if(sensorValues[4] > sensorThreshold){
    moveInch(1);
    readSensor();
    if(sensorValues[0]>sensorThreshold){
      delay(100);
      readSensor();
      if(sensorValues[0]>sensorThreshold && sensorValues[4]>sensorThreshold){
        done();
      }else{
        turnLeft();
        return;
      }
    }
    delay(100);
    readSensor();
    if(sensorValues[0]<sensorThreshold &&sensorValues[1] <sensorThreshold
        && sensorValues[3]<sensorThreshold && sensorValues[4]<sensorThreshold){
          turnRight();
          return;
        }
    moveStraight();
  }
  readSensor();
  if(sensorValues[0]<sensorThreshold && sensorValues[1]<sensorThreshold &&
      sensorValues[2]<sensorThreshold &&sensorValues[3]<sensorThreshold &&
      sensorValues[4]<sensorThreshold){
        turnAround();
      }
}

void moveInch(int times){
  int startTime = millis();
  moveLeftMotor(times*150);
  moveRightMotor(times*150);
  if(times <0) times=(-1)*times;
  while((millis()-startTime)<(times*200));
   moveLeftMotor(0);
  moveRightMotor(0);
}
void turnLeft(){
  //moveInch(1);
  while(analogRead(sensorPin[2])<sensorThreshold ){
    moveLeftMotor(-170);
    moveRightMotor(170);
    delay(20);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(10);
  }
}

void turnRight(){
  //moveInch(1);
  while(analogRead(sensorPin[2])<sensorThreshold ){
    moveLeftMotor(170);
    moveRightMotor(-170);
    delay(20);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(10);
  }
}

void turnAround(){
  //moveInch(1);
  while(analogRead(sensorPin[2])<sensorThreshold ){
    moveLeftMotor(200);
    moveRightMotor(-200);
    delay(20);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(10);
  }
}
void moveStraight(){
  calculate_pid();
  motor_control();
}

void done(){
  moveLeftMotor(0);
  moveRightMotor(0);
  delay(3000);
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














