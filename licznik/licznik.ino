#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27
int period = 1000;
int period2 = 60000;
unsigned long time_now = 0;
unsigned long time_now2 = 0;
int previousOutput;
int flow;
int flow_m;
int flowMinutes;
//Narazie takie parametry bo nwm jakie na pompie będą dane

void setup() {
  lcd.begin(20,4);   // Inicjalizacja LCD 2x16
  lcd.backlight(); // zalaczenie podwietlenia 
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  previousOutput = 0;
  flow = 0;
  Serial.begin(9600);
  pinMode(2, INPUT);
  for(int i = 100; i < 0; i--)
  {
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
  }
}

void loop() {
  int del = analogRead(A0);

  //Co minutę
  if(millis() >= time_now2 + period2){
    time_now2 += period2;
    flowMinutes = flow_m;
    flow_m = 0;
  }

  //Co sekundę
  if(millis() >= time_now + period){
        time_now += period;
        Serial.println(flow);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Flow: ");
        lcd.print(flow);
        lcd.print("/s ");
        lcd.print(flowMinutes);
        lcd.print("/m");
        lcd.setCursor(0,1);
        lcd.print("Delay: ");
        lcd.print(del);
        flow = 0;
  }

  //Obliczanie ticków
  int output = digitalRead(2);
  if(output != previousOutput)
  {
    previousOutput = output;
    flow++;
    flow_m++;
  }
  delay(del);
}
