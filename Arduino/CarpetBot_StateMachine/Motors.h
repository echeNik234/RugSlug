#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Servo.h>
  // Pins and ports needed for the H-bridge to controll the encoder motors
  #define PWM1 3
  #define PWM2 5
  #define IN1 22
  #define IN2 24
  #define IN3 23
  #define IN4 25
  #define ENCA 27
  #define ENCB 29
  #define ENCC 26
  #define ENCD 28
  /////////////////////////////////////////////////////////////////////////

  #define roboServo 10 //pin to connect charging station servo to


  void rotate();
  
  void forwardDrive();

  void reverseDrive(int val);

  void tankLeft(int val);

  void tankRight(int val);

  void beaconLift();
  
  void setPosition(int pos, int pwm, int in1, int in2);

  void setMotor(int dir, int pwmVal, int pwm, int in1, int in2);

  void readEncoder();


#endif