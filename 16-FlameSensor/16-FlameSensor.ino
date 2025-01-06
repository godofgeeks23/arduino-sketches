const int flameSens = A0; // set flame sensor to pin A0
const int speaker = 8;    // set speaker to pin 8
int flameVal;             // set up the data variable for the sensor

void setup()
{

  Serial.begin(9600);        // begin the serial monitor
  pinMode(speaker, OUTPUT);  // define the speaker as an output
  pinMode(flameSens, INPUT); // define flame sensor as an input
}

void loop()
{

  int flameVal = analogRead(flameSens); // read the sensor value of flame sensor

  if (flameVal < 1000)
  { // if the data us less than 1023 then set off an alarm

    digitalWrite(speaker, HIGH);
    Serial.println("FLAME");
  }
  else
  {
    digitalWrite(speaker, LOW); // if else don't set off alarm
    Serial.println("COOL");
  }

  Serial.println(flameVal); // print the data to the serial monitor
  delay(800);
}
