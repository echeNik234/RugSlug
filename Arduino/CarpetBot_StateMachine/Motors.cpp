#include "Motors.h"
#include <Servo.h>
#include <Arduino.h>

Servo myservo; // create servo object to control a servo
int servPos; // variable to store the servo position
int pos = 0;
long prevT = 0;
float eprev = 0;
float eintegral = 0;



// MOTOR FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
void rotate(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(PWM1,255);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(PWM2,255);
}

void forwardDrive(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(PWM1,255);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(PWM2,255);
}


void reverseDrive(int val){
  setPosition(-val, PWM1, IN1, IN2);
  setPosition(-val, PWM2, IN3, IN4);
}


void tankLeft(int val){
  setPosition(-val, PWM1, IN1, IN2);
  setPosition(val, PWM2, IN3, IN4);
}


void tankRight(int val){
  setPosition(val, PWM1, IN1, IN2);
  setPosition(-val, PWM2, IN3, IN4);
}


void setPosition(int pos, int pwm, int in1, int in2){
// set target position
  int target = pos;
  //target = 250*sin(prevT/1e6);
 
  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0;
 
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;
 
  // error
  int e = pos-target;
 
  // derivative
  float dedt = (e-eprev)/(deltaT);
 
  // integral
  eintegral = eintegral + e*deltaT;
 
  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;
 
  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }
 
  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }
 
  // signal the motor
  setMotor(dir,pwr,pwm,in1,in2);
 
  // store previous error
  eprev = e;
}


void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}


void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    pos++;
  }
  else{
    pos--;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// SERVO FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
void beaconLift(){
  if(servPos != 0){
    for (servPos = 90; servPos >= 0; servPos -= 1) { // goes from 90 degrees to 0 degrees
      // in steps of 1 degree
      myservo.write(servPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }

  else{
    for (servPos = 0; servPos <= 90; servPos += 1) { // goes from 0 degrees to 90 degrees
      // in steps of 1 degree
      myservo.write(servPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////