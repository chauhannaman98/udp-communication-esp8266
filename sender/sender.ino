#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "ESPAsyncWebServer.h"

#define PORT 4210

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
char senderPacket[100];
//const int senderPacket = 1;

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

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if(client_status()) {
    digitalWrite(LED_BUILTIN, LOW);
    while (Serial.available() > 0 ) {
      String inputString = Serial.readString();
      inputString.toCharArray(senderPacket, 100);
      if(Udp.beginPacket("192.168.4.2", PORT) &&
        Udp.write(senderPacket) &&
        Udp.endPacket())  {
        Serial.printf("Packet sent: %s\n", senderPacket);
      }
      delay(1000);
    }
  }
  else  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

bool client_status() {
  unsigned char number_client;  
  number_client= wifi_softap_get_station_num();
  
//  Serial.print(" Total Connected Clients are = ");
//  Serial.println(number_client);

  if(number_client == 0)  {
    return false;
  }
  else if(number_client == 1) {
    return true;
  }
}
