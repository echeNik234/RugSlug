#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

  #define IR1 48 // front right sensor
  #define IR2 49 // front left sensor
  #define IR3 50 // back right sensor 
  #define IR4 51 // back left sensor
  #define tiltSensor 52 // tilt sensor
  #define cleanWater 53 // water level sensor for clean tank 
  #define dirtyWater 54 // water level sensor for dirty tank

  int objectDetectedRight();

  int objectDetectedLeft();

  int objectDetectedFront();

  int objectDetectedBack(); 

  int waterLevel(int waterSensor);

  int robotFallenOver();

#endif