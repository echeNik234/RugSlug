#include <WiFiNINA.h>

#include "wifi_network.h"

///////please enter your sensitive data in the Secret tab/wifi_network.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

WiFiServer server(80);

WiFiClient client; // Initialize the client library
// IPAddress server(172, 20, 10, 3);

/* ////////////////
PIN DECLARATIONS
//////////////// */
const int LED_PIN = 9;       // DIGITAL - GPIO, can be used as PWM
const int ANALOG_PIN = 3;    // ANALOG - ADC in, Can be used as GPIO
const int DIGITAL_PIN = 11;  // DIGITAL - GPIO, can be used as PWM

void initHardware() {
  Serial.begin(115200); // Baud rate of serial monitor
  pinMode(DIGITAL_PIN, INPUT_PULLUP); // set digital pin to be input
  pinMode(LED_PIN, OUTPUT); // set led pin to be output
  digitalWrite(LED_PIN, LOW); // set led to be off
}

void connectWiFi() {
  byte ledStatus = LOW; // Set LED status to be off

  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {

    // Print attempt to connect
    // Serial.println(status); // FIX MEE!! Only for testing purposes: get wifi radio status
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  
  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");

  digitalWrite(LED_PIN, LOW); // Set LED to be off
}

void printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
}

void setup() {
  initHardware(); // Set up the pins
  connectWiFi(); // Connect to WiFi
  server.begin();
}

void loop() {
  // check the network connection once every 10 seconds:
  // if (client.connect(server, 80)) {
    printData();
    Serial.println("----------------------------------------");
  // } else {
  //   Serial.println("You're NOT connected to the network, trying to connect");
  //   // status = WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network
  //   Serial.println("----------------------------------------");
  // }
  delay(10000);
}