#include "ChargeSensors.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ezButton.h>

int Liquid_level = 0;
int state;

// ####################### PIN ASSINGMENT ######################
OneWire twoWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensor1(&twoWire); // Pass our oneWire reference to Dallas Temperature.
ezButton limitSwitch1(Lswitch);  // create ezButton object that attach to pin 7;

// ####################### GET TEMP ######################
float getTemp() {
  float temperature;
  sensor1.requestTemperatures();
  temperature = sensor1.getTempFByIndex(0);
  return temperature;
}

// ####################### LIMIT SWITCH ######################
int bumperTriggered() {
  limitSwitch1.loop();  // MUST call the loop() function first

  state = limitSwitch1.getState();
  if (state == HIGH)
    // Serial.println("The limit switch: UNTOUCHED"); // FIX ME: Only for testing purposes
    return 0;
  else
    // Serial.println("The limit switch: TOUCHED"); // FIX ME: Only for testing purposes
    return 1;
}

// ####################### WATER LEVEL SENSOR ######################
int waterLevel() {
  Liquid_level = digitalRead(waterTank);
  if (Liquid_level == 1) {
    return 1;
  } else {
    return 0;
  }
}

// ####################### HEATING ON######################
void heatOn() {
  digitalWrite(waterHeater, HIGH);
}

// ####################### HEATING OFF ######################
void heatOff() {
  digitalWrite(waterHeater, LOW);
}