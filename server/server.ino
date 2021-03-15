#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ESPAsyncWebServer.h"

//#define IP "192.168.4.2"
#define port 4210

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
char senderPacket[] = "Hey! It's a test message";

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
  // put your main code here, to run repeatedly:
  Serial.println(Udp.beginPacket("192.168.4.2", port));
  Udp.write(senderPacket);
  Udp.endPacket();
  delay(1000);
}
