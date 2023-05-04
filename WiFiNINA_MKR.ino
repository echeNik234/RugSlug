#include <SPI.h>
#include <WiFiNINA.h>

#include "wifi_network.h"

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if (status != WL_CONNECTED) {
    Serial.println("Couldn't get a WiFi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to WiFi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  Serial.println("hi");
  Serial.println(client);
  if (client) {
    if (client.connected()) {
      Serial.println("Connected to client");
    } else {
      Serial.println("Not connected to client");
    }
  }
  delay(1000);
}
 