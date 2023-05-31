#include "ChargeMotors.h"
#include "ChargeSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ezButton.h>

// ####################### DEFINES ######################
//global defines
#define PERIOD 5000

// ####################### VARIABLE DECLARATION ######################
//global variables
unsigned long curTime;
unsigned long prevTime = 0;

// ####################### PIN ASSINGMENT ######################
OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensor(&oneWire);  // Temp Sensor: Pass our oneWire reference to Dallas Temperature.
Servo myservo;                       // Dispense Servo: create servo object to control a servo
ezButton limitSwitch(Lswitch);       // Limit switch: create ezButton object that attach to pin 7;

// ####################### CHARGING STATION STATES ######################
typedef enum {
  CHARGING,   //charging station supplies power to robot
  HEATWATER,  //water cleaning solution is heated up
  DISPENSE,   //water cleaning solution is dispensed into robot cleaning tank
  IDLE,       //charging station sits on standby until it detects robot plugging itself back in
} chargeStates;

chargeStates curState = CHARGING;  // IDLE State of SM

// ####################### PIN SET UP ######################
void chargePinSetup() {
  //sensor pins
  pinMode(waterTank, INPUT);        // water level sensor for the chargin station tank
  limitSwitch.setDebounceTime(50);  // bumper switch for the charging station
  //servo pin
  myservo.attach(chargeServo);      // attaches the servo on pin 2 to the servo object.
  //temperature sensor
  sensor.begin();
  //water heater
  pinMode(waterHeater, OUTPUT);
}

// ####################### SET UP ######################
void setup() {
  // put your setup code here, to run once:
  chargePinSetup();
  waterClose();
  Serial.begin(115200);
}

// ####################### STATE MACHINE ######################
void runChargingSwitchCase() {
  switch (curState) {
    //////////////////////////////////////////
    case CHARGING:
      Serial.print("IN CHARGING STATE\n");
      // "Send state of bumper to app"
      // Serial.print(waterLevel()); // FIX ME: Only for testing purposes
      // Serial.print(bumperTriggered()); // FIX ME: Only for testing purposes
      if ((waterLevel() == 0) && (bumperTriggered() == 1)) {
        curState = HEATWATER;
      }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case HEATWATER:
      Serial.print("IN HEATWATER STATE\n");
      // Serial.print("Water is being heated\n");
      heatOn();
      Serial.print(getTemp());  // FIX ME: Only for testing purposes
      if (getTemp() >= 76) {    // 160 deg F
        curState = DISPENSE;
      }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case DISPENSE:
      Serial.print("IN DISPENSE STATE\n");
      waterOpen();
      delay(5000);  // 35000
      waterClose();
      delay(5000);
      heatOff();
      curState = IDLE;
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case IDLE:
      Serial.print("IN IDLE STATE\n");
      if (bumperTriggered() == 1) {
        curState = CHARGING;
      }
      break;
      //////////////////////////////////////////
  }
}

// ####################### LOOP ######################
void loop() {
  // put your main code here, to run repeatedly:
  curTime = millis();
  runChargingSwitchCase();
}
