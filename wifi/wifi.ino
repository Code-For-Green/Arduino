#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "ZSPWrzesnia_nau";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "eSzkola78()";     // The password of the Wi-Fi network

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

void SendData(const char* request)
{
 if (client.connect("www.xxxxx.xxx",80)) { // REPLACE WITH YOUR SERVER ADDRESS
 client.println("GET add2.php HTTP/1.1"); 
 client.println("Host: xxx.xxx.xxx"); // SERVER ADDRESS HERE TOO
 client.println("Content-Type: application/x-www-form-urlencoded"); 
 client.print("Content-Length: "); 
 client.println(data.length()); 
 client.println(); 
 client.print(data); 
 } 
}
