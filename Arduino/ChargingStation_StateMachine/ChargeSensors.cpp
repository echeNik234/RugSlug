#include "ChargeSensors.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>


  // Data wire is plugged into pin 2 on the Arduino
  #define ONE_WIRE_BUS 6
  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  OneWire oneWire(ONE_WIRE_BUS);
  // Pass our oneWire reference to Dallas Temperature. 
  DallasTemperature sensors(&oneWire);
  
  int Liquid_level = 0;


  float getTemp(){
    float temperature;
    sensors.requestTemperatures();
    temperature = sensors.getTempFByIndex(0);
    return temperature;
  }


  int bumperTriggered(){
    if( (digitalRead(Lswitch) == LOW)){
      return 1;
    }

    if( (digitalRead(Lswitch) == HIGH)){
      return 0;
    }
  }


  int waterLevel(){
    Liquid_level = digitalRead(waterTank)
    if(Liquid_level == 1){
      return 1;
    }
    else{
      return 0;
    }
  }