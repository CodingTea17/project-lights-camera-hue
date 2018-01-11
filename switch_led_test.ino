#define led 15

int slideSwitch = 13;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(slideSwitch, INPUT);
}

void loop() {  
  if(!digitalRead(slideSwitch)) digitalWrite(led, HIGH);
  if(digitalRead(slideSwitch)) digitalWrite(led, LOW);
}
