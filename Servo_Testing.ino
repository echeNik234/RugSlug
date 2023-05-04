// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 9; 
// Create a servo object 
Servo Servo1; 
void setup() { 
  Serial.begin(115200);
  
   // We need to attach the servo to the used pin number 
  Servo1.attach(servoPin); 
  Servo1.write(0); 
  delay(1000); 
  Servo1.write(90);
  delay(1000);
  Servo1.write(-90); 
  delay(1000); 
}
void loop(){ 
   // Make servo go to 0 degrees 
  //  Servo1.write(0); 
  //  delay(1000); 
  //  // Make servo go to 90 degrees 
  //  Servo1.write(90); 
  //  delay(1000); 
   // Make servo go to 180 degrees 
  //  Serial.println("Degree");
  //  Servo1.write(255); 
  //  delay(1000); 
   
}