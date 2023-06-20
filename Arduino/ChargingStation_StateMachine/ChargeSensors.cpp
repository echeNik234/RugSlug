#include "ChargeSensors.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ezButton.h>
  
  int Liquid_level = 0;
  int state;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire twoWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensor1(&twoWire);

ezButton limitSwitch1(Lswitch);  // create ezButton object that attach to pin 7;

  float getTemp(){
    float temperature;
    sensor1.requestTemperatures();
    temperature = sensor1.getTempFByIndex(0);
    return temperature;
  }


  int bumperTriggered(){
    limitSwitch1.loop(); // MUST call the loop() function first

  // if(limitSwitch1.isPressed())
  //   Serial.println("The limit switch: UNTOUCHED -> TOUCHED");

  // if(limitSwitch1.isReleased())
  //   Serial.println("The limit switch: TOUCHED -> UNTOUCHED");

  state = limitSwitch1.getState();
  if(state == HIGH)
    // Serial.println("The limit switch: UNTOUCHED");
    return 0;
  else
    // Serial.println("The limit switch: TOUCHED");
    return 1;
  }


  int waterLevel(){
    Liquid_level = digitalRead(waterTank);
    if(Liquid_level == 1){
      return 1;
    }
    else{
      return 0;
    }
  }


  void heatOn(){
    digitalWrite(waterHeater, HIGH);
  }


  void heatOff(){
    digitalWrite(waterHeater, LOW);
  }
