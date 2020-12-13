#include "WaterFlowSensor.h"
#include <ESP8266WiFi.h>

void ConnectToServer()
{
    WiFi.begin(SSID, PASSWORD);             // Connect to the network
    Serial.print("Connecting to ");
    Serial.print(SSID);
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}