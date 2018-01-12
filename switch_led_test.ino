int slideSwitch = 13;
bool slideState = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(slideSwitch, INPUT);
}

void loop() {  
  if(!digitalRead(slideSwitch)) { 
    slideState = false;
  }
  if(digitalRead(slideSwitch)) {
    slideState = true;
  }

  switch (slideState) {
  case true:
    digitalWrite(LED_BUILTIN, HIGH); 
    break;
  case false:
    digitalWrite(LED_BUILTIN, LOW); 
    break;
  default:
    // Nada
    break; 
  }
}
