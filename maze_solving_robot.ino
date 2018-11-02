#include "Robot.h"
#include "pinConfig.h"




int sensorWhiteMin = 20; // this is done because at a st black line                           //, at some point , all sensor values are less than sensorThreshold                                         
int sensorWhiteMax = 40;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  nodeSerial.begin(115200);
  
  pinMode(13,HIGH);
  digitalWrite(13,LOW);
  initializeMotor();
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
while(0){
//nodeSerial.println("hello world");
readSensor();
}
moveStraight();
readSensor();
rightHandWall();


}

void rightHandWall(){

 if(sensorValues[0] < sensorWhiteMax && 
    sensorValues[1] < sensorWhiteMax &&
    sensorValues[2] < sensorWhiteMax &&
    sensorValues[3] < sensorWhiteMax &&
    sensorValues[4] < sensorWhiteMax){
      
      moveInch(1);
      nodeSerial.println("B");
      turnLeft();
    }
 if(sensorValues[0] > sensorThreshold && sensorValues[2]>sensorThreshold && sensorValues[4]>sensorThreshold){
  //since the right most sensor is abit forward, this configuration is not being detected.
  digitalWrite(13,HIGH);

  moveInch(1);
  delay(50);
  readSensor();
  if( sensorValues[0] > sensorThreshold && sensorValues[4]>sensorThreshold){
    done();
    delay(5000);
  }
   nodeSerial.println("R");
  turnRight();
}

else if(sensorValues[0] < sensorThreshold && sensorValues[4] > sensorThreshold){
 
  moveInch(1);
  readSensor();
  if( sensorValues[0] > sensorThreshold && sensorValues[4]>sensorThreshold){
    done();
    delay(5000);
  }
   else if(sensorValues[0] < sensorThreshold){
     nodeSerial.println("R");
  turnRight();
  }
}

else if(sensorValues[0] > sensorThreshold){

  moveInch(1); 
  readSensor();
  if(sensorValues[2] >sensorThreshold || sensorValues[1] > sensorThreshold || sensorValues[3] >sensorThreshold){
    moveStraight();
  }else{
     nodeSerial.println("L");
    turnLeft();
  }

}
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














