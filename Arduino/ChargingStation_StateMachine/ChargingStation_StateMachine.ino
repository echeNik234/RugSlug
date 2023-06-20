#include "ChargeMotors.h"
#include "ChargeSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ezButton.h>
#include <WiFiNINA.h>
#include "wifi_network.h"

// ####################### DEFINES ######################
//global defines
#define PERIOD 5000

// ####################### VARIABLE DECLARATION ######################
//global variables
unsigned long curTime;
unsigned long prevTime = 0;

// ####################### WIFI VARIABLES ######################
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;      //connection status
WiFiServer server(80);            //server socket
WiFiClient client = server.available();
int ledPin = 11;
int wifiPin = 9;//10;
int startBtn = 0;

// ####################### PIN ASSINGMENT ######################
OneWire oneWire(ONE_WIRE_BUS);       // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensor(&oneWire);  // Temp Sensor: Pass our oneWire reference to Dallas Temperature.
Servo myservo;                       // Dispense Servo: create servo object to control a servo
ezButton limitSwitch(Lswitch);       // Limit switch: create ezButton object that attach to pin 7;

// ####################### CHARGING STATION STATES ######################
typedef enum {
  CHARGING,   //charging station supplies power to robot
  HEATWATER,  //water cleaning solution is heated up
  DISPENSE,   //water cleaning solution is dispensed into robot cleaning tank
  IDLE,       //charging station sits on standby until it detects robot plugging itself back in
} chargeStates;

chargeStates curState = CHARGING;  // IDLE State of SM

// ####################### PIN SET UP ######################
void chargePinSetup() {
  // IoT pins
  pinMode(ledPin, OUTPUT); // FIX ME: LED CONTROL
  pinMode(wifiPin, OUTPUT); // LED signal: Solid on = Connected to WiFi & blnk Led = trying to connect
  //sensor pins
  pinMode(waterTank, INPUT);        // water level sensor for the chargin station tank
  limitSwitch.setDebounceTime(50);  // bumper switch for the charging station
  //servo pin
  myservo.attach(chargeServo);      // attaches the servo on pin 2 to the servo object.
  //temperature sensor
  sensor.begin();
  //water heater
  pinMode(waterHeater, OUTPUT);
  // beacon in charging station
  pinMode(beaconCS, OUTPUT);
}

// ####################### SET UP ######################
void setup() {
  // put your setup code here, to run once:
  chargePinSetup();
  waterClose();
  Serial.begin(115200);
  // while (!Serial); // FIX ME: Only for testing purposes

  // WiFi connection
  enable_WiFi();
  connect_WiFi();
  server.begin();
  printWifiStatus();
  waterOpen();
  delay(35000);  // 35000
  waterClose();
}

// ####################### STATE MACHINE ######################
void runChargingSwitchCase() {
  switch (curState) {
    //////////////////////////////////////////
    case CHARGING:
      Serial.print("IN CHARGING STATE\n");
      // "Send state of bumper to app" // FIX ME

      // IoT connection info
      // delay(5000);
      printWEB();
      // delay(5000);

      Serial.print(waterLevel()); // FIX ME: Only for testing purposes
      Serial.print(bumperTriggered()); // FIX ME: Only for testing purposes
      Serial.print(startBtn); // FIX ME: Only for testing purposes
      if ((waterLevel() == 0) && (bumperTriggered() == 1) && (startBtn == 1)) { //) { // && (startBtn == 1)) {
        curState = HEATWATER;
        startBtn = 0;
      }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case HEATWATER:
      Serial.print("IN HEATWATER STATE\n");
      // Serial.print("Water is being heated\n");
      heatOn();
      Serial.print(getTemp());  // FIX ME: Only for testing purposes
      if (getTemp() >= 160) {    // 160 deg F
        curState = DISPENSE;
      }
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case DISPENSE:
      Serial.print("IN DISPENSE STATE\n");
      waterOpen();
      delay(35000);  // 35000
      waterClose();
      delay(5000);
      heatOff();
      curState = IDLE;
      break;
    //////////////////////////////////////////


    //////////////////////////////////////////
    case IDLE:
      beaconCSOff();
      delay(300000);// 5 min = 300000
      beaconCSOn();
      delay(1000);//300000);
      Serial.print("IN IDLE STATE\n");
      if (bumperTriggered() == 1) {
        curState = CHARGING;
      }
      break;
      //////////////////////////////////////////
  }
}

// ####################### LOOP ######################
void loop() {
  // put your main code here, to run repeatedly:
  curTime = millis();

  client = server.available();

  if (client) {
    printWEB();
  } 
  // delay(5000);

  // Charging Station SM
  // runChargingSwitchCase();


}

// ################### CONNECTED WIFI INFO #######################
void printWifiStatus() {
  // print the SSID of the network you're attached to: // FIX ME: Only for testing purposes
  Serial.print("SSID: "); // FIX ME: Only for testing purposes
  Serial.println(WiFi.SSID()); // FIX ME: Only for testing purposes

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: "); // FIX ME: Only for testing purposes
  Serial.println(ip); // FIX ME: Only for testing purposes

  digitalWrite(wifiPin, HIGH);
}

// ################### WIFI MODULE CHECK #######################
void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!"); // FIX ME: Only for testing purposes
    // don't continue
    while (true);
  }
}

// ################### CONNECT TO WIFI #######################
void connect_WiFi() {
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: "); // FIX ME: Only for testing purposes
    Serial.println(ssid); // FIX ME: Only for testing purposes
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    blinkLED(); // FIX ME: Only for testing purposes
  }
  
}

// ################### BLINK LED #######################
void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(wifiPin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);                      // wait for a second
    digitalWrite(wifiPin, LOW);   // turn the LED off by making the voltage LOW
    delay(100);                      // wait for a second
  }
}

// ################### WEB SERVER HANDLING #######################
void printWEB() {
  if (client) {                             // if you get a client,
    // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
           
            //create the buttons
            client.print("Click <a href=\"/H\">here</a> to start cleaning process<br>");
            client.print("Click <a href=\"/L\">here</a> to refresh data<br><br>");
            
            // int randomReading = analogRead(A1);
            // client.print("Random reading from analog pin: ");
            // client.print(randomReading);

            // CHARGING STATION TANK
            client.print("Water Level in Charging Station: ");
            // client.println(waterLevel());
            // client.println();
            if (waterLevel() == 0) { // Good
              client.println("Good");
              client.println();
            } else { // Bad
              client.println("Refill");
              client.println();
            }

            client.println();

            // CHARGING STATION TANK TEMPERATURE
            client.print(" .............. ");
            client.print("Temperature: ");
            client.println(getTemp());
            client.println();


            

           
            
        
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Commands Web server link
        if (currentLine.endsWith("GET /H")) {
          // Serial.println("LED HIGH"); // FIX ME
          digitalWrite(ledPin, HIGH);    
          startBtn = 1;    
        }
        if (currentLine.endsWith("GET /L")) {
          // Serial.println("LED LOW"); // FIX ME
          digitalWrite(ledPin, LOW);       
        }

      }
    }
    // close the connection:
    client.stop();
    // Serial.println("client disconnected"); // FIX ME: Only for testing purposes
    // digitalWrite(wifiPin, LOW);    
  } 
}
