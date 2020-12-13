#pragma once

#define BAUDRATE 115200

#define SSID "ZSPWrzesnia_nau"
#define PASSWORD "eSzkola78()"

//LCD Module
void LCDPrintNew();

//WiFi module
void ConnectToServer();
void SendToDataBase();