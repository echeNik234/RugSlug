#ifndef CHARGESENSORS_H
#define CHARGESENSORS_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

  #define waterTank 1 // water level sensor for station tank
  #define ONE_WIRE_BUS 6 // for connection to tempereature sensor
  #define Lswitch 7 // bumper switch to detect robot at station

  float getTemp();

  int bumperTriggered();

  int waterLevel();
#endif