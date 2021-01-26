

// LCD jest wykomentowane bo nie dziala jak nie jest podlaczone




#include <Wire.h>   // standardowa biblioteka Arduino
//#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define BAUDRATE 115200
#define SSID "ZSPWrzesnia_nau"
#define PASSWORD "eSzkola78()"

//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
WiFiClient client;

const char* server_address = "codeforgreen.zspwrzesnia.pl";
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
      //LCDPrint(500);
      SendData(500);
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

void LCDPrint(int sum)
{
      /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Flow: ");
      lcd.print(flow);
      lcd.print("/s ");
      lcd.print(sum);
      lcd.print("/m");
      lcd.setCursor(0,1);
      lcd.print("Delay: ");
      lcd.print(time_delay);*/
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
  HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://codeforgreen.zspwrzesnia.pl/woda/public/api/add.php?flow=" + String(flow));  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    } else {
      Serial.println("Error: ");
      Serial.println(httpCode);
    }
 
    http.end();   //Close connection
}
