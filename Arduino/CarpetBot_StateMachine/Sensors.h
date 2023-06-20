 #ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

  #define IR1 22 // front right sensor
  #define IR2 23 // front left sensor
  #define tiltSensor 40 // tilt sensor
  #define cleanWater 41 // water level sensor for clean tank 
  #define dirtyWater 42 // water level sensor for dirty tank
  #define farBeaconSensor 39 // beacon detector for distance 
  #define closeBeaconSensor A1 // beacon detector for up close

  int objectDetectedRight();

  int objectDetectedLeft(); 

  int objectDetectedFront();

  // int objectDetectedBack(); 

  int waterLevel(int waterSensor);

  int robotFallenOver();

  int farBeaconDetected();

  int closeBeaconDetected();

#endif
