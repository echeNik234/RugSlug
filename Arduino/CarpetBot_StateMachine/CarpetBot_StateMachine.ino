#include "Motors.h"
#include "Sensors.h"
#include <Servo.h>


//global defines
int beacClose;
int beacFar;
double voltage;
int tilt;

//global variables
  //timer 1
unsigned long prevTime1 = 0;
unsigned long curTime1;
const long period1 = 3000;

//timer 2
unsigned long prevTime2 = 0;
unsigned long curTime2;
unsigned long forwardDuration = 4000;

//timer 3
unsigned long prevTime3 = 0;
unsigned long curTime3;
unsigned long turnDuration = 7000;

int flag = 0;
int numCycles = 1;
int cycleCount = 0;
bool turning = false;
unsigned long startTime;
int cleaningState;
int repeatCount = 2;
int totalCount = 2;
int testFlag = 1;



Servo clawServo; // create servo object to control claw of beacon grabber
Servo waterServo; // create servo object to control solution dispensing

typedef enum
{
  CHARGING, //robot charges its battery at charging station
  FLUIDFILL, //water cleaning solution is put into the robots cleaning tank
  BEACONSEARCH, //robot begins searching for then navigating to spot beacon 
  BEACONGRAB, //robot picks up the beacon
  CLEANING, //robot begins cleanig stain
  CHARGINGSEARCH, //robot begins searching for then navigating to charging statio beacon
  PAUSE //robot functions are paused from app or when bot is tipped over
} roboStates; 

roboStates curState = CHARGING;
roboStates prevState = CHARGING;

//function that sets up the output and input pins to be called in void setup()
void pinSetup(){
//HBridge pins
    //left motor
  pinMode(PWM1,OUTPUT); //we have to set PWM pin as output
  pinMode(IN1,OUTPUT); //Logic pins are also set as output
  pinMode(IN2,OUTPUT);

    //right motor
  pinMode(PWM2,OUTPUT); //we have to set PWM pin as output
  pinMode(IN3,OUTPUT); //Logic pins are also set as output
  pinMode(IN4,OUTPUT);

//servo pins
  clawServo.attach(clawPin);// attaches the claw servo to pin 11 to the servo object.
  waterServo.attach(waterPin);// attaches the water servo to pin 12 to the servo object.

//sensor pins
  pinMode(IR1, INPUT); // front right sensor
  pinMode(IR2, INPUT); // front left sensor
  pinMode(tiltSensor, INPUT); // tilt sensor
  pinMode(cleanWater, INPUT); // water level sensor for clean tank
  pinMode(cleanWater, INPUT); // water level sensor for dirty tank
  pinMode(farBeaconSensor, INPUT); // beacon detector for detecting from a distance
  pinMode(closeBeaconSensor, INPUT); // beacon detector for detecting up close
  // prevTime2 = millis();

//arm pins
  pinMode(arm1, OUTPUT);
  pinMode(arm2,OUTPUT);
  pinMode(armPwm, OUTPUT);

// brush pins
  pinMode(brush1, OUTPUT);
  pinMode(brush2,OUTPUT);
  pinMode(brushPwm, OUTPUT);

// fan pin  
  pinMode(fanPin, OUTPUT);
}




void setup() {
  // put your setup code here, to run once:
  pinSetup();
  Serial.println("1. yes");
  Serial.println("2. no");
  Serial.begin(115200);
}



//global variables for switch cases here



void runRoboSwitchCase()
//implement switch case for top level here
{
  switch (curState)
  {
    //////////////////////////////////////////
    case CHARGING: {
      Serial.println("Would you like to initiate cleaning? Enter 1 for yes or 2 for no:");
      while (Serial.available() == 0){      
      }
      int choice = Serial.parseInt();

      switch (choice){
        case 1:
          Serial.print("Entering FLUIDFILL state\n");
          curState = FLUIDFILL;
        break;

        case 2:
          Serial.println("Staying in charging state");
          curState = CHARGING;
        break;

        default:
          Serial.println("Not a valid answer please try again");
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case FLUIDFILL:{
      delay(5000);
      Serial.print("Entering BEACONSEARCH state\n");
      curState = BEACONSEARCH;
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case BEACONSEARCH:{
      if(robotFallenOver() == 0){
        Serial.print("Robot fallen over\n");
        Serial.print("Entering PAUSE state\n");
        prevState = BEACONSEARCH;
        curState = PAUSE;
      }

      // if(batteryCharge() <= 13.00){
      //   Serial.print("Battery low");
      //   Serial.print('\n');
      //   curState = CHARGINGSEARCH;
      // }
      
      if(flag == 0){
        reverseDrive();
      }

      if(curTime1 - prevTime1 >= period1){ //set prevTime equal to curTime at end of entire process
        flag = 1;
        stop();
      }

      if(flag == 1){ //reset at end of entire process
        if(farBeaconDetected() == 0){
          forwardDrive();
                
          if(objectDetectedLeft() == 1 && objectDetectedRight() == 0){
            Serial.print("Object on the left\n");
            tankRight();
            delay(1250);
            forwardDrive();
            delay(1000);
          }

          if(objectDetectedRight() == 1 && objectDetectedLeft() == 0){
            Serial.print("Object on the right\n");
            tankLeft();
            delay(1250);
            forwardDrive();
            delay(1000);
          }

          if(objectDetectedFront() == 1){
            Serial.print("Object in front\n");
            tankRight();
            delay(1250);
            forwardDrive();
            delay(1000);
          }
        }
        if (farBeaconDetected() == 1){
          rotate();
        }
      }


      if(closeBeaconDetected() == 1){
        Serial.print("Entering BEACONGRAB state\n");
        curState = BEACONGRAB;
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case BEACONGRAB:{
      if(robotFallenOver() == 0){
        Serial.print("Robot fallen over\n");
        Serial.print("Entering PAUSE state\n");
        prevState = BEACONSEARCH;
        curState = PAUSE;
      }

      if(batteryCharge() <= 13.0){
        Serial.print("Battery low");
        Serial.print('\n');
        curState = CHARGINGSEARCH;
      }
      stop();
      delay(1000);
      clawOpen();
      delay(1000);
      beaconLower();
      delay(3000);
      clawStop();
      forwardDrive();
      delay(500);
      stop();
      clawClose();
      delay(1000);
      beaconLift();
      delay(3000);
      clawStop();
      Serial.print("Entering CLEANING state\n");
      Serial.print("\n");
      curState = CLEANING;
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CLEANING:{
      unsigned long currentTime = millis();

      if(robotFallenOver() == 0){
        Serial.print("Robot fallen over\n");
        Serial.print("Entering PAUSE state\n");
        prevState = CLEANING;
        curState = PAUSE;
      }

      // if(batteryCharge() <= 13.00){
      //   // Serial.print("Battery low");
      //   // Serial.print('\n');
      //   curState = CHARGINGSEARCH;
      // }

      if(cleaningState == 0){
        brushOn();
        openWater();
        fanOn();
        forwardScrub();
        startTime = currentTime;
        cleaningState = 1;
      }
      else if(cleaningState == 1 && currentTime - startTime >= forwardDuration){
        stop();
        startTime = currentTime;
        cleaningState = 2;
      }
      else if(cleaningState == 2){
        rotate();
        startTime = currentTime;
        cleaningState = 3;
      }
      else if(cleaningState == 3 && currentTime - startTime >= turnDuration){
        stop();
        cleaningState = 0;
        repeatCount--;
        Serial.print(repeatCount);
        Serial.print("\n");
        if(repeatCount > 0){
          cleaningState = 0;
        }
        else{
          repeatCount = totalCount;
          brushOff();
          closeWater();
          fanOff();
          Serial.print("Entering CHARGINGSEARCH state\n");
          curState = CHARGINGSEARCH;
        }
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CHARGINGSEARCH:{
      if(robotFallenOver() == 0){
        Serial.print("Robot fallen over\n");
        Serial.print("Entering PAUSE state\n");
        prevState = BEACONSEARCH;
        curState = PAUSE;
      }

      if(farBeaconDetected() == 0){
        forwardDrive();
              
        if(objectDetectedLeft() == 1 && objectDetectedRight() == 0){
          Serial.print("Object on the left\n");
          tankRight();
          delay(1250);
          forwardDrive();
          delay(500);
        }

        if(objectDetectedRight() == 1 && objectDetectedLeft() == 0){
          Serial.print("Object on the right\n");
          tankLeft();
          delay(1250);
          forwardDrive();
          delay(500);
        }

        if(objectDetectedFront() == 1){
          Serial.print("Object in front\n");
          tankRight();
          delay(1250);
          forwardDrive();
          delay(500);
        }
      }
      if (farBeaconDetected() == 1){
        rotate();
      }

      if(closeBeaconDetected() == 1){
        flag = 0;
        prevTime1 = curTime1;
        stop();
        Serial.print("Entering CHARGING state\n");
        curState = CHARGING;
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case PAUSE:{

      stop();
      clawStop();
      brushOff();
      fanOff();
      if(robotFallenOver() == 1){
        Serial.print("Entering previous state\n");
        curState = prevState;
      }
      break;
    }
    //////////////////////////////////////////
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  curTime1 = millis();
  curTime2 = millis();
  curTime3 = millis();

  
//////////////////////////////////////////////////////////
  runRoboSwitchCase();
//////////////////////////////////////////////////////////
    //  voltage = batteryCharge();
    //  Serial.print(voltage);
    //  Serial.print("\n");
}
