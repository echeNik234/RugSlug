//motor test
int motorPin = 3;

//HBridge test
const int pwm = 2 ; //initializing pin 2 as pwm
const int in_1 = 22 ;
const int in_2 = 24 ;

//IR test
int IRSensor = 36;

// Servo test, knob and sweep
#include <Servo.h>
Servo myservo; // create servo object to control a servo, knob snd sweep
int potpin = 0; // analog pin used to connect the potentiometer, knob
int val; // variable to read the value from the analog pin, knob
int pos; // variable to store the servo position, sweep

// Bumper switch test
int Lswitch = 4;

// Motor + encoder test
#define ENC_IN_RIGHT_A 7
volatile long right_wheel_pulse_count = 0;

// Water Level test
int Liquid_level = 0;

//tilt sensor test
const int tiltPin = 1;

// #define motor_test
// #define HBridge_test
// #define IRSensor_test
// #define Servo_test_knob
// #define Servo_test_sweep
// #define BumperSwitch_test
// #define MotorEncoder_test
// #define WaterLevel_test
#define TiltSensor_test




/////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  #ifdef HBridge_test
    pinMode(pwm,OUTPUT); //we have to set PWM pin as output
    pinMode(in_1,OUTPUT); //Logic pins are also set as output
    pinMode(in_2,OUTPUT);
  #endif


  #ifdef IRSensor_test
    pinMode(IRSensor, INPUT);
    Serial.begin(115200);
  #endif


  myservo.attach(10); // attaches the servo on pin 10 to the servo object. knob and sweep


  #ifdef BumperSwitch_test
    Serial.begin(115200);
    pinMode(Lswitch, INPUT); 
  #endif


  #ifdef MotorEncoder_test
    Serial.begin(115200);
    pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
  #endif


  #ifdef WaterLevel_test
    pinMode(5, INPUT);
    Serial.begin(115200);
  #endif


  #ifdef TiltSensor_test
    Serial.begin(115200);
    pinMode(tiltPin, INPUT);
    digitalWrite(tiltPin, HIGH);
  #endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  #ifdef motor_test
    digitalWrite(motorPin, HIGH);
  #endif


  #ifdef HBridge_test
    //For Clock wise motion , in_1 = High , in_2 = Low
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,LOW) ;
    analogWrite(pwm,255) ;
    /* setting pwm of the motor to 255, we can change the speed of rotation
    by changing pwm input, since we are only using arduino we are using highest
    value to drive the motor */
    //Clockwise for 3 secs
    delay(3000) ;
    //For brake
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,HIGH) ;
    delay(1000) ;
    //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    delay(3000) ;
    //For brake
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,HIGH) ;
    delay(1000) ;
  #endif


  #ifdef IRSensor_test
    int Sensordata = digitalRead(IRSensor);
    Serial.print("Sensor Value: ");
    Serial.print(Sensordata);
    Serial.print("\n");
    delay(1000);
  #endif


  #ifdef Servo_test_knob
    val = analogRead(potpin); // reads the value of the potentiometer (value between 0 and 1023)
    val = map(val, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)
    myservo.write(val); // sets the servo position according to the scaled value
    delay(15); // waits for the servo to get there
  #endif


  #ifdef Servo_test_sweep
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  #endif


  #ifdef BumperSwitch_test
    if( (digitalRead(Lswitch) == LOW)) {
      Serial.println("door is closed"); 
      delay(100); 
    }

    if( (digitalRead(Lswitch) == HIGH)) {
      Serial.println("door is opened"); 
      delay(100); 
    }
  #endif


  #ifdef MotorEncoder_test
    Serial.print(" Pulses: ");
    Serial.println(right_wheel_pulse_count);  
  #endif


  #ifdef WaterLevel_test
    Liquid_level = digitalRead(5);
    if(Liquid_level == 1){
      Serial.print("Water level high\n");
    }
    if(Liquid_level == 0){
      Serial.print("Water level low\n");
    }
    delay(2000);
  #endif


  #ifdef TiltSensor_test
    if(digitalRead(tiltPin)){
      Serial.print("tilted\n");      
    }
    else{
      Serial.print("not tilted\n");
    }
    delay(2000);  
  #endif
}

// Increment the number of pulses by 1
void right_wheel_pulse() {
  right_wheel_pulse_count++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////