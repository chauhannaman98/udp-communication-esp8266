#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

WiFiUDP Udp;

unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char replyPacket[] = "Got message successfully!";  // a reply string to send back


void setup()  {
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  pinMode(LED_BUILTIN, OUTPUT);

  // turn off by default
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  Serial.println(WiFi.status());
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Resetting ESP. . .");
    ESP.reset();
  }
  else  {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)  {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents:%s\n", incomingPacket);
    
    if(strcmp(incomingPacket, "true")==10)  {
      digitalWrite(LED_BUILTIN, LOW); // turn led ON
    }
    else if(strcmp(incomingPacket, "false")==10) {
      digitalWrite(LED_BUILTIN, HIGH);  //turn led OFF
    }

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
  }
  }
}
