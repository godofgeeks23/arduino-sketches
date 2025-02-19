// Includes the Servo library
#include <Servo.h>.

// Defines Trig and Echo pins of the Ultrasonic Sensor, and pin for servo motor
const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 12;

// define delay interval in ms to set servo rotation speed
const int delayInterval = 20;

// set baud rate for the serial communication
const int serialBaudRate = 9600;

// servo start and end angles in degrees
const int servoStartAngle = 15;
const int servoEndAngle = 165;

// Variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(serialBaudRate);
  myServo.attach(servoPin); // Defines on which pin is the servo motor attached
}

void loop()
{
  // rotates the servo motor from start angle to end angle
  for (int i = servoStartAngle; i <= servoEndAngle; i++)
  {
    myServo.write(i);
    delay(delayInterval);
    distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

    Serial.print(i);        // Sends the current degree into the Serial Port
    Serial.print(",");      // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print(".");      // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from end angle to start angle
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
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}