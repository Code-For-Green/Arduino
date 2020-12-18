#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "ZSPWrzesnia_nau";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "eSzkola78()";     // The password of the Wi-Fi network

const char* username = "249391552_0000017";
const char* password = "1CsbP8pQd4T@";

const char* server_address = "serwer1727017.home.pl";

WiFiClient client;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { }

void SendData(int flow)
{
  if (client.connect(server_address ,80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.print("GET add.php?user="); 
    client.print(username);
    client.print("&pass");
    client.print(password);
    client.print("&flow");
    client.print(flow);
    client.print(" HTTP/1.1");
    client.println()
    client.print("Host: "); // SERVER ADDRESS HERE TOO
    client.println(server_address);;
    client.println("Connection: close");
    client.println();
  } 
}
