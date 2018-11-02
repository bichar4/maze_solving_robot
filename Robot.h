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


float Kp=1,Ki=0,Kd=0.6;double error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;

int initial_motor_speed=200;
int turningSpeed = 200;
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

