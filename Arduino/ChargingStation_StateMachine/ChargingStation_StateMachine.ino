#include "ChargeMotors.h"
#include "ChargeSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ezButton.h> 

//global defines
#define PERIOD 5000

//global variables 
//timer 1
unsigned long prevTime = 0;
unsigned long curTime;
const long period1 = 3000;


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensor(&oneWire);

Servo myservo; // create servo object to control a servo

ezButton limitSwitch(Lswitch);  // create ezButton object that attach to pin 7;

typedef enum
{
  CHARGING, //charging station supplies power to robot
  HEATWATER, //water cleaning solution is heated up 
  DISPENSE, //water cleaning solution is dispensed into robot cleaning tank
  IDLE, //charging station sits on standby until it detects robot plugging itself back in
} chargeStates;

chargeStates curState = CHARGING;
chargeStates prevState = CHARGING;

void chargePinSetup(){

//sensor pins
  pinMode(waterTank, INPUT); // water level sensor for the chargin station tank
  limitSwitch.setDebounceTime(50); // bumper switch for the charging station  

//servo pin
  myservo.attach(chargeServo); // attaches the servo on pin 2 to the servo object.

//temperature sensor
  sensor.begin();

//water heater
  pinMode(waterHeater, OUTPUT);

// beacon in charging station
  pinMode(beaconCS, OUTPUT);
}



void setup() {
  // put your setup code here, to run once:
  chargePinSetup();
  // waterOpen();
  // delay(3000);
  waterClose();
  // chargeStates curState = CHARGING;
  Serial.begin(115200);

}

void runChargingSwitchCase()
{
  switch (curState)
  {
    //////////////////////////////////////////
    case CHARGING: 
      // Serial.print("IN CHARGING STATE\n");
      // "Send state of bumper to app"
      if((waterLevel() == 1) && (bumperTriggered() == 1)){
        Serial.print("Entering HEATWATER state\n");
        curState = HEATWATER;
      }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case HEATWATER:
      heatOn();
      Serial.print(getTemp());
      Serial.print("\n");
      if(getTemp() >= 100){
        Serial.print("Entering DISPENSE state\n");
        curState = DISPENSE;
      }
      // curState = DISPENSE;
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case DISPENSE:
    if(bumperTriggered() == 1){ 
      // Serial.print("IN DISPENSE STATE\n");
      waterOpen();
      delay(35000);
      waterClose();
      delay(5000);
      heatOff();
      Serial.print("Entering IDLE state\n");
      curState = IDLE;
    }
    else{
      Serial.print("Entering IDLE state\n");
      prevState = DISPENSE;
      curState = IDLE;
    }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case IDLE: 
      // Serial.print("IN IDLE STATE\n");
      beaconCSOff();
      delay(5000);
      beaconCSOn();
      if(bumperTriggered() == 1){
        beaconCSOff();
        Serial.print("Entering CHARGING state\n");
        curState = CHARGING;
      }
      else if(bumperTriggered() == 1 && prevState == DISPENSE){
        beaconCSOff();
        Serial.print("Entering DISPENSE state\n");
        prevState == CHARGING;
        curState = DISPENSE;
      }
      break;
    //////////////////////////////////////////
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  curTime = millis();
  // Serial.print(getTemp());
  // Serial.print("\n");
  runChargingSwitchCase();

  // heatOn();

}
