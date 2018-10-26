/*void initializeMotor();
 * void moveLeftMotor(int Speed);
 * void moveRightMotor(int Speed);
 */



#define  leftMotorP 9
#define leftMotorM  8
#define rightMotorP  11
#define rightMotorM  10
#define leftSpeedPin  5
#define rightSpeedPin  6

void initializeMotor(){
  pinMode(leftMotorP, OUTPUT);
  pinMode(leftMotorM, OUTPUT);
  pinMode(rightMotorP, OUTPUT);
  pinMode(rightMotorM, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(leftSpeedPin,OUTPUT);
  analogWrite(rightSpeedPin,0);
  analogWrite(leftSpeedPin,0);
}

void moveLeftMotor(int Speed){
  if(Speed >0){
     digitalWrite(leftMotorP,HIGH);
     digitalWrite(leftMotorM, LOW);
     analogWrite(leftSpeedPin,Speed);
  
  }else{
    digitalWrite(leftMotorP,LOW);
     digitalWrite(leftMotorM, HIGH);
     analogWrite(leftSpeedPin,-Speed);
  }
 
}

void moveRightMotor(int Speed){
  if(Speed >0){
     digitalWrite(rightMotorP,HIGH);
     digitalWrite(rightMotorM, LOW);
     analogWrite(rightSpeedPin,Speed);
  
  }else{
    digitalWrite(rightMotorP,LOW);
     digitalWrite(rightMotorM, HIGH);
     analogWrite(rightSpeedPin,-Speed);
  }
 
}

