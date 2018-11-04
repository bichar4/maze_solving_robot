/*
 * 
 * void turnRight()
 * void turnLeft()
 * void turnAround()
 * moveStraight()
 * done()
 */

#include "motors.h"
#include "sensors.h"
#include "pinConfig.h"

char path[50] = {};
int pathLength = 0;


float Kp=1,Ki=0,Kd=0.6;double error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;

int initial_motor_speed=200;
int turningSpeed = 210;
int turningRunTime = 10;
int turningHoldTime = 15;

int sensorThreshold = 100;

void calculate_pid()
{   int position = readLine();
    error = position-BASEPOSITION;
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = ((Kp*P) + (Ki*I) + (Kd*D))/15;
    
    previous_I=I;
    previous_error=error;
}


void motor_control(){
  //Calculate the effective motor speed
  int leftSpeed = (initial_motor_speed+(PID_value*speedFactor));
  int rightSpeed = (initial_motor_speed-PID_value);
  //THe motor speed shouldnot exceed max PWM
  leftSpeed = constrain(leftSpeed,0,255);
  rightSpeed = constrain(rightSpeed,0,255);

  moveLeftMotor(leftSpeed);
  moveRightMotor(rightSpeed);

}


void turnRight(){
  //moveInch(1);

  while(analogRead(sensorPin[2])>sensorThreshold){
    moveLeftMotor(turningSpeed);
    moveRightMotor(-turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
  }
  while(analogRead(sensorPin[4])<sensorThreshold){
      turningSpeed -= 20;
       moveRightMotor(-turningSpeed);
    moveLeftMotor(turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
     turningSpeed += 20;    
    }
  while(analogRead(sensorPin[2])<sensorThreshold ){
    moveLeftMotor(turningSpeed);
    moveRightMotor(-turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
  }
  delay(100);
}

void turnLeft(){
  //moveInch(1);

    while(analogRead(sensorPin[2])>sensorThreshold){
          moveRightMotor(turningSpeed);
          moveLeftMotor(-turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
    }
    while(analogRead(sensorPin[0])<sensorThreshold){
      turningSpeed -= 20;
       moveRightMotor(turningSpeed);
    moveLeftMotor(-turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
     turningSpeed += 20;  
  
    }
  while(analogRead(sensorPin[2])<sensorThreshold ){
  
    moveRightMotor(turningSpeed);
    moveLeftMotor(-turningSpeed);
    delay(turningRunTime);
    moveLeftMotor(0);
    moveRightMotor(0);
    delay(turningHoldTime);
  }
  delay(100);
}


void turnAround(){
 turnLeft();
}
void moveStraight(){
  calculate_pid();
  motor_control();
   
}

void done(){
  moveLeftMotor(0);
  moveRightMotor(0);
}


void moveInch(int times){
  int startTime = millis();
  moveLeftMotor(times*200*speedFactor);
  moveRightMotor(times*200);
  if(times <0) times=(-1)*times;
  while((millis()-startTime)<(times*50));
   moveLeftMotor(0);
  moveRightMotor(0);
  delay(100);
 
}

void simplify(){
    if(pathLength<3 || path[pathLength-2] !='B') return;
    
    int totalAngle=0;
    int i;
    
    for(i=1;i<=3;i++){
        switch(path[pathLength-i]){
            case 'R':
            totalAngle+=90;
            break;
            
            case 'B':
            totalAngle+= 180;
            break;
            
            case 'L':
            totalAngle += 270;
            break;
        }
    }
    
    totalAngle = totalAngle%360;
    switch(totalAngle){
        case 0:
        path[pathLength-3] = 'S';
        break;
        
        case 90:
        path[pathLength-3] = 'R';
        break;
        
        case 180:
        path[pathLength-3] = 'B';
        break;
        
        case 270:
        path[pathLength-3] = 'L';
        break;
    }
    
    pathLength -=2;
}
