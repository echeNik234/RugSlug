#include "Motors.h"
#include "Sensors.h"
// #include <Servo.h>


//global defines
#define DEGREE_360 2096
#define DEGREE_180 1048 
#define DEGREE_90 524
#define DEGREE_45 262 


//global variables
  //for calcuating encoder values
// int pos = 0;
// long prevT = 0;
// float eprev = 0;
// float eintegral = 0;

  //for servo
// int servPos; // variable to store the servo position

typedef enum
{
  CHARGING, //robot charges its battery at charging station
  FLUIDFILL, //water cleaning solution is put into the robots cleaning tank
  BEACONSEARCH, //robot begins searching for then navigating to spot beacon 
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
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);

    //right motor
  pinMode(PWM2,OUTPUT); //we have to set PWM pin as output
  pinMode(IN3,OUTPUT); //Logic pins are also set as output
  pinMode(IN4,OUTPUT);
  pinMode(ENCC,INPUT);
  pinMode(ENCD,INPUT);

//servo pin
  myservo.attach(10);// attaches the servo to pin 10 to the servo object.

//sensor pins
  pinMode(IR1, INPUT); // front right sensor
  pinMode(IR2, INPUT); // front left sensor
  pinMode(IR3, INPUT); // back right sensor
  pinMode(IR4, INPUT); // back left sensor
  pinMode(tiltSensor, INPUT); // tilt sensor
  pinMode(cleanWater, INPUT); // water level sensor for clean tank
  pinMode(cleanWater, INPUT); // water level sensor for dirty tank
}





void setup() {
  // put your setup code here, to run once:
  pinSetup();
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  attachInterrupt(digitalPinToInterrupt(ENCC),readEncoder,RISING);
  roboStates curState = CHARGING;
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
      if (waterLevel(cleanWater) == 1){
          curState = BEACONSEARCH;
      }

    break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case BEACONSEARCH:{
      // beaconLift();
      if(robotFallenOver() == 1 || ("signal from app to pause cleaning")){
        prevState = BEACONSEARCH;
        curState = PAUSE;
      }
      if("stain beacon detected"){
        forwardDrive();
      }
      
      if("stain beacon is not detected"){
        rotate();
      }

      if(objectDetectedRight() == 1){
        tankLeft(DEGREE_180);
      }

      if(objectDetectedLeft() == 1){
        tankRight(DEGREE_180);
      }

      if (objectDetectedFront() == 1){
        int i = 0;
        if(i != 2){
          reverseDrive(DEGREE_360);
          i++;
        }
      }

      if ("stain beacon detected as close(implementation not figured out)"){
        beaconLift();
        curState = CLEANING;        
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CLEANING:{

      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case CHARGINGSEARCH:{
      if(robotFallenOver() == 1 || ("signal from app to pause cleaning")){
        prevState = CHARGINGSEARCH;
        curState = PAUSE;
      }
      if("charge beacon detected"){
        forwardDrive();
      }
      
      if("charge beacon is not detected"){
        rotate();
      }

      if(objectDetectedRight() == 1){
        tankLeft(DEGREE_180);
      }

      if(objectDetectedLeft() == 1){
        tankRight(DEGREE_180);
      }

      if (objectDetectedFront() == 1){
        int i = 0;
        if(i != 2){
          reverseDrive(DEGREE_360);
          i++;
        }
      }

      if("charge beacon detected as close(implementation not figured out)"){
        curState = CHARGING;        
      }
      break;
    }
    //////////////////////////////////////////


    //////////////////////////////////////////
    case PAUSE:{
      if(robotFallenOver() == 0){
        curState = prevState;
      }

      if("Signal from app to resume cleaning"){
        curState = prevState;
      }
      break;
    }
    //////////////////////////////////////////
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  runRoboSwitchCase();
  //  forwardDrive();
  //     if(objectDetectedRight() == 1){
  //       tankLeft(DEGREE_180);
  //     }
  //     if(objectDetectedLeft() == 1){
  //       tankRight(DEGREE_180);
  //     }
  //     if (objectDetectedFront() == 1){
  //       int i = 0;
  //       if(i != 2){
  //         reverseDrive(DEGREE_360);
  //         i++;
  //       }
  //       tankRight(DEGREE_180);
  //     }
   

}
