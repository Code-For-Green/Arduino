#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Ustawienie adresu ukladu na 0x27
int period = 1000;
unsigned long time_now = 0;
int previousOutput;
int flow;

int minute_data[60] = { };
int avalible_array = 0;

int time_delay;

//Narazie takie parametry bo nwm jakie na pompie będą dane

void setup() {
  lcd.begin(20,4);   // Inicjalizacja LCD 2x16
  lcd.backlight(); // zalaczenie podwietlenia 
  lcd.setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
  previousOutput = 0;
  flow = 0;
  time_delay = 50;
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
        avalible_array = 0;
      minute_data[avalible_array] = flow;
      avalible_array++;
      time_now += period;
      
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
      lcd.setCursor(0,2);
      lcd.print("Moisture: ");
      lcd.print(analogRead(A1));
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
