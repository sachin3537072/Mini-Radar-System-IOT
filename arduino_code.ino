// Includes the Servo library
#include <Servo.h>. 
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
const int led=13;
const int BUZZER = 2;
const int servo=12;
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(servo); // Defines on which pin is the servo motor attached
}
void loop() {
  //code for buzzer
  
  // rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++){  
  myServo.write(i);
  delay(15);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  if(distance<40)
  {
      digitalWrite(led,HIGH);
      tone(BUZZER, 85);
  }
   else if(distance>40)
  {
    digitalWrite(led,LOW);
    noTone(BUZZER);
  }
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 180 to 0 degrees
  for(int i=180;i>=0;i--){  
  myServo.write(i);
  delay(15);
  distance = calculateDistance();
   if(distance<=40)
  {
      digitalWrite(13,HIGH);
      tone(BUZZER, 85);
  }
  else if(distance>40)
  {
    digitalWrite(13,LOW);
    noTone(BUZZER);
  }
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}