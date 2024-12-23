int delayms = 50;
int numLEDs = 6;
void setup() {
  unsigned char ledPin;                          //ledPin will be set to 1,2,3,4,5,6, 7 and 8.
  for (ledPin = 1; ledPin <= numLEDs; ledPin++)  //In turn set 1 ~ 8 digital pins to output mode
    pinMode(ledPin, OUTPUT);                     //Set the  ledPin pin to output mode
}

void loop() {
  unsigned char ledPin;                          //ledPin will be set to 1,2,3,4,5,6, 7 and 8.
  for (ledPin = 1; ledPin <= numLEDs; ledPin++)  //Every 200ms on in order LED1 ~ 8
  {
    digitalWrite(ledPin, HIGH);  //led on
    delay(delayms);              //Delay delayms ms
  }
  for (ledPin = 1; ledPin <= 8; ledPin++)  //Every delaymsms off in order LED1 ~ 8
  {
    digitalWrite(ledPin, LOW);  //led off
    delay(delayms);             //Delay delayms ms
  }
}
