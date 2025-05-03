// Include the Servo library
#include <Servo.h>.

// Defines trig and echo pins of the Ultrasonic Sensor, and pin for servo motor
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;

// define delay interval (in ms) to set servo rotation speed
const int delayInterval = 20;

// define baud rate for the serial communication
const int serialBaudRate = 9600;

// define servo start and end angles (in degrees)
const int servoStartAngle = 15;
const int servoEndAngle = 165;

// declare variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

// initialize pin modes, serial and servo
void setup()
{
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT);  // Set the echoPin as an Input
  Serial.begin(serialBaudRate);
  myServo.attach(servoPin); // Define on which pin is the servo motor attached
}

void loop()
{
  // rotate the servo motor from start angle to end angle
  for (int i = servoStartAngle; i <= servoEndAngle; i++)
  {
    myServo.write(i);
    delay(delayInterval);
    distance = calculateDistance(); // calculating the distance measured by the Ultrasonic sensor for each degree
    // print info on the serial monitor
    Serial.print(i);        // Send the current degree into the Serial Port
    Serial.print(",");      // Send addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Send the distance value into the Serial Port
    Serial.print(".");      // Send addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeat for end angle to start angle
  for (int i = servoEndAngle; i > servoStartAngle; i--)
  {
    myServo.write(i);
    delay(delayInterval);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Read the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}