#include "WaterFlowSensor.h"

#define BAUDRATE 115200
#define SSID "ZSPWrzesnia_nau"
#define PASSWORD "eSzkola78()"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
WiFiClient client;

const char* server_address = "serwer1727017.home.pl";
const char* username = "249391552_0000017";
const char* password = "1CsbP8pQd4T@";

int period = 1000;
unsigned long time_now = 0;
int previousOutput;
int time_delay;

int flow;
int minute_data[60] = { };
int avalible_array = 0;

void setup()
{
	Serial.begin(BAUDRATE);
	ConnectToServer();
}

void loop()
{
    //Ustawianie delayu  
   while(Serial.available()) {
      time_delay = Serial.read();
   }
  //Co sekundę
  if(millis() >= time_now + period)
  {
      int sum = 0;
      for(int &data : minute_data)
      {
        sum += data;
      }
      if(avalible_array == 60)
      {
        avalible_array = 0;
      }
      minute_data[avalible_array] = flow;
      avalible_array++;
      time_now += period;
      LCDPrint();
      flow = 0;
  }

  //Obliczanie ticków
  int output = digitalRead(2);
  if(output != previousOutput)
  {
    previousOutput = output;
    flow++;
  }
  delay(time_delay);
}

void LCDPrint()
{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Flow: ");
      lcd.print(flow);
      lcd.print("/s ");
      lcd.print(sum);
      lcd.print("/m");
      lcd.setCursor(0,1);
      lcd.print("Delay: ");
      lcd.print(time_delay);
}

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
    client.println();
    client.print("Host: "); // SERVER ADDRESS HERE TOO
    client.println(server_address);;
    client.println("Connection: close");
    client.println();
  } 
}