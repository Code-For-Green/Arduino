int period = 1000;
unsigned long time_now = 0;
int previousOutput;
int flow;

//Narazie takie parametry bo nwm jakie na pompie będą dane

void setup() {
  previousOutput = 0;
  flow = 0;
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {

  //Co sekundę
  if(millis() >= time_now + period){
        time_now += period;
        Serial.println(flow);
        flow = 0;
  }

  //Obliczanie ticków
  int output = digitalRead(2);
  if(output != previousOutput)
  {
    previousOutput = output;
    flow++;
  }
  delay(analogRead(A0));
}
