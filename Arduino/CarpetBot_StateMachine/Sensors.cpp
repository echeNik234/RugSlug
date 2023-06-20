#include "Sensors.h"
#include <Arduino.h>

  int Liquid_level = 0;

  int objectDetectedRight(){
    if(digitalRead(IR1) == LOW){
      return 1;
    }
    else{
      return 0;
    }
  }


  int objectDetectedLeft(){
    if(digitalRead(IR2) == LOW){
      return 1;
    }
    else{
      return 0;
    }
  }


  int objectDetectedFront(){
    if((digitalRead(IR1) == LOW) && (digitalRead(IR2) == LOW)){
      return 1;
    }
    else{
      return 0;
    }

  }


  int waterLevel(int waterSensor){
    Liquid_level = digitalRead(waterSensor);
    if(Liquid_level == 1){
      return 1;
    }
    else{
      return 0;
    }
  }

  int robotFallenOver(){
    if(digitalRead(tiltSensor)){
      return 1;
    }
    else{
      return 0;
    }
  }


  int farBeaconDetected(){
    if(digitalRead(farBeaconSensor)){
      return 1;
    }
    else{
      return 0;
    }
  }


  int closeBeaconDetected(){
    int val = 0;
    val = analogRead(closeBeaconSensor);
    return val;
    // int sum = 0;
    // int sample = 100;
    // for (int i = 0; i < sample; i++) {
    //   sum += analogRead(closeBeaconSensor);
    // }
    // // less than 400 not detecting
    // return sum / sample;
  }
