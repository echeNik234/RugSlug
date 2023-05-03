#include "ChargeMotors.h"
#include <Servo.h>
#include <Arduino.h>

Servo myservo; // create servo object to control a servo
int chargeServPos; // variable to store the servo position

void waterRelease(){
  if chargeServPos != 0){
    for  chargeServPos = 180; chargeServPos >= 0; chargeServPos -= 1) { // goes from 90 degrees to 0 degrees
      // in steps of 1 degree
      myservo.write chargeServPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }

  else{
    for  chargeServPos = 0; chargeServPos <= 180; chargeServPos += 1) { // goes from 0 degrees to 90 degrees
      // in steps of 1 degree
      myservo.write chargeServPos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}