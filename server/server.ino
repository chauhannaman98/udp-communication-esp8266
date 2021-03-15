#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ESPAsyncWebServer.h"

#define PORT 4210

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
//char senderPacket[] = "Hey! It's a test message";
const int senderPacket = 1;

AsyncWebServer server(80);
WiFiUDP Udp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin(); 
}

void loop() {
  if(Udp.beginPacket("192.168.4.2", PORT))
    Serial.println("Packet sent");
  Udp.write(senderPacket);
  Udp.endPacket();
  delay(1000);
}
