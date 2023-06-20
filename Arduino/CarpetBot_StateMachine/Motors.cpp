#include "Motors.h"
#include <Servo.h>
#include <Arduino.h>

extern Servo armServo; // create servo object to control arm of beacon grabber
extern Servo clawServo; // create servo object to control claw of beacon grabber
extern Servo waterServo; // create servo object to control solution dispensing


// MOTOR FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
void stop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}


void rotate(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);


  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
}


void forwardDrive(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
}


void reverseDrive(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
}


void tankLeft(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
}


void tankRight(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(PWM1,255);
  analogWrite(PWM2,255);
}


void brushOn(){
  digitalWrite(brush1,HIGH);
  digitalWrite(brush2,LOW);

  analogWrite(brushPwm,255);
}


void brushOff(){
  digitalWrite(brush1,LOW);
  digitalWrite(brush2,LOW);

  analogWrite(brushPwm,255);
}

void fanOn(){
  digitalWrite(fanPin, HIGH);
}


void fanOff(){
  digitalWrite(fanPin, LOW);
}

void beaconLift(){
  digitalWrite(arm1,LOW);
  digitalWrite(arm2,HIGH);

  analogWrite(armPwm,255);
}


void beaconLower(){
  digitalWrite(arm1,HIGH);
  digitalWrite(arm2,LOW);

  analogWrite(armPwm,255);
}


void clawStop(){
  digitalWrite(arm1,LOW);
  digitalWrite(arm2,LOW);
}


void forwardScrub(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(PWM1,65);
  analogWrite(PWM2,85);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// SERVO FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
void clawOpen(){
  clawServo.write(0);
}


void clawClose(){
  clawServo.write(90);
}


void openWater(){
  waterServo.write(0);
}


void closeWater(){
  waterServo.write(120);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
