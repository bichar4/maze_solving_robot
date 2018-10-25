/*
 * void readSensor()
 * void calibrate()
 * void showCalibrated()
 * void readCalibrated()
 * int readLine()
 */


#define NUMSENSORS 5
#define BASEPOSITION 2000
unsigned int calibratedMin[NUMSENSORS] = {35,35,35,35,35};
unsigned int calibratedMax[NUMSENSORS]= {750,700,700,850,700};
int sensorPin[NUMSENSORS] = {A0,A1,A2,A3,A4};
int sensorValues[NUMSENSORS];

//checked 
void readSensor(){
  for(int i=0;i<NUMSENSORS;i++){
    sensorValues[i] = analogRead(sensorPin[i]);
  }
//  for(int i =0;i<NUMSENSORS;i++){
//    Serial.print(sensorValues[i]);
//    Serial.print("===");
//    
//  }
//  Serial.println(" ");
}

//checked 
void calibrate(){
  
  int i,j;
  int max_sensor_values[NUMSENSORS];
  int min_sensor_values[NUMSENSORS];
 
  for(j = 0;j<10;j++){
    readSensor();
    for(i = 0;i<NUMSENSORS;i++){
      if(j == 0 || max_sensor_values[i] < sensorValues[i]){
        max_sensor_values[i] = sensorValues[i];  
      }

      if(j ==0 || min_sensor_values[i]>sensorValues[i]){
        min_sensor_values[i] = sensorValues[i];
      }
    }
  }
  

  for(i = 0;i<NUMSENSORS;i++){
    if(min_sensor_values[i] > calibratedMax[i])
       calibratedMax[i] = min_sensor_values[i];
    if(max_sensor_values[i] < calibratedMin[i])
       calibratedMin[i] = max_sensor_values[i];   
  }


}

void showCalibrated(){

    for(int i = 0;i<NUMSENSORS;i++){
    calibratedMin[i] = 1023;
    calibratedMax[i]= 0;
  }

  int previousTime = millis();
  while(millis()-previousTime < 10000){
    digitalWrite(13,HIGH);
    calibrate();
  }
  digitalWrite(13,LOW);
  
  Serial.println("CalibratedMax");
  for(int i=0;i<NUMSENSORS;i++){
    Serial.print(calibratedMax[i]);
    Serial.print("----");
  }
  Serial.println();

  Serial.println("CalibratedMin");
  for(int i=0;i<NUMSENSORS;i++){
    Serial.print(calibratedMin[i]);
    Serial.print("----");
  }
  Serial.println("Calibration done");
    
}
// Returns values calibrated to a value between 0 and 1000, where
// 0 corresponds to the minimum value read by calibrate() and 1000
// corresponds to the maximum value.  Calibration values are
// stored separately for each sensor, so that differences in the
// sensors are accounted for automatically.
//checked
void readCalibrated(){
  int i;
  readSensor();
  for(i=0;i<NUMSENSORS;i++){
    unsigned int calmin,calmax;
    unsigned int denominator;

    denominator = calibratedMax[i] - calibratedMin[i];

    signed int x = 0;
    if(denominator != 0){
      x = (((signed long)sensorValues[i])-calibratedMin[i])*1000/denominator;
    }
    if(x<0) x = 0;
    else if(x>1000) x = 1000;

    sensorValues[i] = x;
    //Serial.print(sensorValues[i]);
    //Serial.print("==");
  } 
  //Serial.println(" ");
  
}

int readLine(){
  unsigned char i, on_line =0;
  unsigned long avg; //this is for the weighted total,
                      //which is long before division
  unsigned int sum;//this is for denominator
  static int last_value=0;//assume initially that the line is left
  readCalibrated();

  avg =0;
  sum = 0;

  for(i =0;i<NUMSENSORS;i++){
    int value = sensorValues[i];
   // sensorValues[i] = value;
    //keep track of whether we see the line at all
    if(value >10){
      on_line = 1;
    }

    //only average in values that are above a noise threshold

    if(value > 0){
      avg +=(long)(value)*(i*1000);
      sum+=value;
    }
    
  }

  if(!on_line){
    //If it last read to the left of center, return 0.
    if(last_value <(NUMSENSORS-1)*1000/2) return 0;
    //If it last read to the right of center, return the max
    else return (NUMSENSORS-1)*1000;
  }

  last_value = avg/sum;

  return last_value;
                      
}


