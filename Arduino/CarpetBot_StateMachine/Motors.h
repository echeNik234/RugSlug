#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
  // Pins and ports needed for the H-bridge to control the encoder motors
  #define PWM1 3
  #define PWM2 5
  #define IN1 51
  #define IN2 53
  #define IN3 52
  #define IN4 50
  
  //Pins and ports for the claw arm motor
  #define arm1 47
  #define arm2 46
  #define armPwm 2
  #define brush1 28
  #define brush2 27
  #define brushPwm 9
  /////////////////////////////////////////////////////////////////////////

  #define clawPin 12 //pin to connect claw servo to pwm pin 12
  #define waterPin 13 //pin to connect water dispense servo to pwm pin 13
  #define fanPin 29 //pin to connect fan to pin 29

  void stop();

  void rotate();
  
  void forwardDrive();

  void reverseDrive();

  void tankLeft();

  void tankRight();

  void beaconLift();
  
  void beaconLower();

  void clawOpen();

  void clawClose();

  void clawStop();

  void openWater();

  void closeWater();

  void brushOn();

  void brushOff();

  void fanOn();

  void fanOff();

  void forwardScrub();

#endif
