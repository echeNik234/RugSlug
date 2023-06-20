#ifndef CHARGESENSORS_H
#define CHARGESENSORS_H

// #include <OneWire.h>
// #include <DallasTemperature.h>
#include <Arduino.h>

  #define waterTank 1 // water level sensor for station tank
  #define ONE_WIRE_BUS 6 // for connection to tempereature sensor
  #define Lswitch 7 // bumper switch to detect robot at station
  #define waterHeater 8 //pin for turning on an off the water heater
  #define beaconCS 10 // pin for turning on and off the beacon

  float getTemp();

  int bumperTriggered();

  int waterLevel();

  void heatOn();

  void heatOff();

  void beaconCSOn();

  void beaconCSOff();
#endif
