#include "Sensors.h"
#include <Arduino.h>

  int Liquid_level = 0; 
  int lastTiltState = LOW;
  unsigned long debounceDelay = 50;
  unsigned long lastDebounceTime = 0;
  const int numReadings1 = 50; // Number of readings to average for far beacon
  const int numReadings2 = 50; // Number of readings to average for close beacon
  const int numReadings3 = 50; // Number of readings to average for battery

  int farBeacon[numReadings1]; // Array to store readings for far beacon
  int index1 = 0; // Index for the current reading of far beacon
  int total1 = 0; // Running total of readings for far beacon
  int average1 = 0; // Average value for far beacon

  int closeBeacon[numReadings2]; // Array to store readings for close beacon
  int index2 = 0; // Index for the current reading of close beacon
  int total2 = 0; // Running total of readings for close beacon
  int average2 = 0; // Average value for close beacon

  double batVolt[numReadings3]; // Array to store readings for battery voltage
  int index3 = 0; // Index for the current reading of battery
  double total3 = 0.0; // Running total of readings for battery
  double average3 = 0.0; // Average value for battery
  double divRatio = 0.08968;
  double ampGain = 3.384;

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
    // int tiltState = digitalRead(tiltSensor);
    // if (tiltState != lastTiltState) {
    //   unsigned long currentMillis = millis();

    //   if (currentMillis - lastDebounceTime > debounceDelay) {
    //     lastTiltState = tiltState;
    //     lastDebounceTime = currentMillis;
    //     return tiltState;
    //   }
    // }
    // return LOW;
    if(digitalRead(tiltSensor)){
      return 1;
    }
    else{
      return 0;
    }
  }


  int farBeaconDetected(){
    int val = 0;
    int num = 0;
    val = analogRead(farBeaconSensor);
    // Subtract the oldest reading from the total
    total1 = total1 - farBeacon[index1];
    // Store the new reading in the array
    farBeacon[index1] = val;
    // Add the new reading to the total
    total1 = total1 + val;
    // Move to the next index
    index1 = (index1 + 1) % numReadings1;
  
    // Calculate the average
    average1 = total1 / numReadings1;
    if (average1 <= 435){
      // Serial.print("Output not detected\n");
      num = 0;
    }
    if(average1 >= 440){
      // Serial.print("Output detected\n");
      num = 1;
    }
    return num;
  }


  int closeBeaconDetected(){
    int val = 0;
    int num = 0;
    val = analogRead(closeBeaconSensor);
    // Subtract the oldest reading from the total
    total2 = total2 - closeBeacon[index2];
    // Store the new reading in the array
    closeBeacon[index2] = val;
    // Add the new reading to the total
    total2 = total2 + val;
    // Move to the next index
    index2 = (index2 + 1) % numReadings2;
  
    // Calculate the average
    average2 = total2 / numReadings2;
    if (average2 <= 625){
      // Serial.print("Output not detected\n");
      num = 0;
    }
    if(average2 >= 635){
      // Serial.print("Output detected\n");
      num = 1;
    }
    return num;
  }

  double batteryCharge(){
    double batVal = 0;
    double ampVltg;
    double batVltg;
    batVal = analogRead(batteryFuel);
    ampVltg = (batVal *5)/1023;
    batVltg = ampVltg/(divRatio*ampGain);

    // Subtract the oldest reading from the total
    total3 = total3 - batVolt[index3];
    // Store the new reading in the array
    batVolt[index3] = static_cast<double>(batVltg);
    // Add the new reading to the total
    total3 = total3 + batVolt[index3];
    // Move to the next index
    index3 = (index3 + 1) % numReadings3;
  
    // Calculate the average
    average3 = total3 / numReadings3;
    return average3;
  }
