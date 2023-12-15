#include "ChargeMotors.h"
#include <Servo.h>
#include <Arduino.h>

extern Servo myservo; // create servo object to control a servo
int chargeServPos = 0; // variable to store the servo position

void waterOpen(){
  Serial.print("Water Open\n");
  myservo.write(-90);
}

void waterClose(){
  Serial.print("Water Close\n");
  myservo.write(90);
}
