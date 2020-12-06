#define FLOW_RAW_MIN 0
#define FLOW_RAW_MAX 1023
#define FLOW_CONV_MIN 0
#define FLOW_CONV_MAX 255

//Narazie takie parametry bo nwm jakie na pompie będą dane

void setup() {
  Serial.begin(9600);
}

void loop() {
  int output = map(analogRead(A0), FLOW_RAW_MIN, FLOW_RAW_MAX, FLOW_CONV_MIN, FLOW_CONV_MAX);
  Serial.println(output);
  delay(100);
}
