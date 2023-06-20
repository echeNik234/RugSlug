#include "Motors.h"
#include "Sensors.h"
#include <Servo.h>


//global defines



//global variables
  //timer 1
unsigned long prevTime1 = 0;
unsigned long curTime1;
const long period1 = 3000;

//timer 2
unsigned long prevTime2 = 0;
unsigned long curTime2;
const int forwardDuration = 4000;

//timer 3
unsigned long prevTime3 = 0;
unsigned long curTime3;
const int turnDuration = 7000;

int flag = 0;
int numCycles = 8;
int cycleCount = 0;
bool turning = false;





Servo clawServo; // create servo object to control claw of beacon grabber
Servo waterServo; // create servo object to control solution dispensing

typedef enum
{
  CHARGING, //robot charges its battery at charging station
  FLUIDFILL, //water cleaning solution is put into the robots cleaning tank
  BEACONSEARCH, //robot begins searching for then navigating to spot beacon 
  CLEANING, //robot begins cleanig stain
  CHARGINGSEARCH, //robot begins searching for then navigating to charging statio beacon
  PAUSE //robot functions are paused from app or when bot is tipped over
} roboStates; 

roboStates curState = BEACONSEARCH;
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
  prevTime2 = millis();

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
      if("app signal detected"){
          curState = FLUIDFILL;
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case FLUIDFILL:{
      if (waterLevel(cleanWater) == 1 && waterLevel(dirtyWater) == 0){
          curState = BEACONSEARCH;
      }
    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case BEACONSEARCH:{
      if(robotFallenOver() == 1){
        prevState = BEACONSEARCH;
        curState = PAUSE;
      }

      if(flag == 0){
        reverseDrive();
      }

      if(curTime1 - prevTime1 >= period1){ //set prevTime equal to curTime at end of entire process
        flag = 1;
        stop();
      }

      if(flag == 1){ //reset at end of entire process
        if(farBeaconDetected() == 1){
          forwardDrive();
                
          if(objectDetectedLeft() == 1 && objectDetectedRight() == 0){
            tankRight();
            delay(1250);
            forwardDrive();
            delay(1000);
          }

          if(objectDetectedRight() == 1 && objectDetectedLeft() == 0){
            tankLeft();
            delay(1250);
            forwardDrive();
            delay(1000);
          }

          if(objectDetectedFront() == 1){
            tankRight();
            delay(1250);
            forwardDrive();
            delay(1000);
          }
        }
        if (farBeaconDetected() == 0){
          rotate();
        }
      }


      if((closeBeaconDetected() <= 0) && (closeBeaconDetected() >= -3)){
        stop();
        delay(1000);
        clawOpen();
        delay(1000);
        beaconLower();
        delay(7000);
        clawStop();
        forwardDrive();
        delay(500);
        stop();
        clawClose();
        delay(1000);
        beaconLift();
        delay(8000);
        clawStop();
        curState = CLEANING;
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CLEANING:{
      if(robotFallenOver() == 1){
        prevState = CLEANING;
        curState = PAUSE;
      }

      brushOn();
      openWater();
      //turn fan on

      if(cycleCount != numCycles){

        if(turning == false){
          forwardScrub();
        }

        if(curTime2 - prevTime2 >= forwardDuration){
          stop();
          turning = true;
        }

        if(turning == true){
          rotate();
        }

        if(curTime3 - prevTime3 >= turnDuration){
          prevTime3 = curTime3;
          prevTime2 = curTime2;
          stop();
          cycleCount += 1;
          turning = false;
        }
      }     
  
      if(cycleCount == numCycles){
        cycleCount = 0;
        brushOff();
        closeWater();
        //turn off fan
        curState = CHARGINGSEARCH; 
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CHARGINGSEARCH:{
      if(farBeaconDetected() == 1){

        forwardDrive();
              
        if(objectDetectedLeft() == 1 && objectDetectedRight() == 0){
          tankRight();
          delay(1250);
          forwardDrive();
          delay(1000);
        }

        if(objectDetectedRight() == 1 && objectDetectedLeft() == 0){
          tankLeft();
          delay(1250);
          forwardDrive();
          delay(1000);
        }

        if(objectDetectedFront() == 1){
          tankRight();
          delay(1250);
          forwardDrive();
          delay(1000);
        }
      }
      if (farBeaconDetected() == 0){
        rotate();
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case PAUSE:{
      if(robotFallenOver() == 0){
        curState = prevState;
      }

      // if("Signal from app to resume cleaning"){
      //   curState = prevState;
      // }
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

  runRoboSwitchCase();

  // if(robotFallenOver() == 1){
  //       prevState = BEACONSEARCH;
  //       curState = PAUSE;
  //     }

  //     if(flag == 0){
  //       reverseDrive();
  //     }

  //     if(curTime1 - prevTime1 >= period1){ //set prevTime equal to curTime at end of entire process
  //       flag = 1;
  //       stop();
  //     }

  //     if(flag == 1){ //reset at end of entire process
  //       if(farBeaconDetected() == 1){
  //         forwardDrive();
                
  //         if(objectDetectedLeft() == 1 && objectDetectedRight() == 0){
  //           tankRight();
  //           delay(1250);
  //           forwardDrive();
  //           delay(1000);
  //         }

  //         if(objectDetectedRight() == 1 && objectDetectedLeft() == 0){
  //           tankLeft();
  //           delay(1250);
  //           forwardDrive();
  //           delay(1000);
  //         }

  //         if(objectDetectedFront() == 1){
  //           tankRight();
  //           delay(1250);
  //           forwardDrive();
  //           delay(1000);
  //         }
  //       }
  //       if (farBeaconDetected() == 0){
  //         rotate();
  //       }
  //     }


  //     if((closeBeaconDetected() <= 0) && (closeBeaconDetected() >= -3)){
  //       stop();
  //       delay(1000);
  //       clawOpen();
  //       delay(1000);
  //       beaconLower();
  //       delay(7000);
  //       clawStop();
  //       forwardDrive();
  //       delay(500);
  //       stop();
  //       clawClose();
  //       delay(1000);
  //       beaconLift();
  //       delay(8000);
  //       clawStop();
  //       curState = CLEANING;
  //     }
}
