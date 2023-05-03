#include "ChargeMotors.h"
#include "ChargeSensors.h"


//global defines
#define PERIOD 5000

//global variables 
unsigned int curTime;
unsigned int prevTime;

typedef enum
{
  CHARGING, //charging station supplies power to robot
  HEATWATER, //water cleaning solution is heated up 
  DISPENSE, //water cleaning solution is dispensed into robot cleaning tank
  IDLE, //charging station sits on standby until it detects robot plugging itself back in
} chargeStates;

chargeStates curState = CHARGING;

void chargePinSetup(){

//sensor pins
  pinMode(waterTank, INPUT); // water level sensor for the chargin station tank
  pinMode(Lswitch, INPUT); // bumper switch for the charging station  

//servo pin
  myservo.attach(0); // attaches the servo on pin 0 to the servo object.
}

void setup() {
  // put your setup code here, to run once:
  chargePinSetup();
  chargeStates curState = CHARGING;
  Serial.begin(115200);

}

void runChargingSwitchCase()
{
  switch (curState):
  {
    //////////////////////////////////////////
    case CHARGING: {
      if("app signal detected" && (waterLevel() == 1)){
          curState = FLUIDFILL;
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case HEATWATER: {
      "Turn on water heater"
      if(getTemp() >= 160){
        curState = DISPENSE;
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case DISPENSE: {
      waterRelease();
      if(curTime - prevTime == PERIOD){
        waterRelease();
        "Turn off water heater"
        curState = IDLE;
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case IDLE: {
      if(bumperTriggered() == 1){
        curState = CHARGING
      }
    break;
    }
    //////////////////////////////////////////
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  runChargingSwitchCase();

}
