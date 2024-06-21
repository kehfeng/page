/*
Main code of the interactive object.
*/

#include <Servo.h>
Servo myservo; 

int echoPin = 10; 
int trigPin = 9;
int ledRed = 13;
int ledYellow = 12;
int ledGreen = 11;
int ledWhite = 7;
int speaker = 2;
int servo = 5;

long duration;
int distance;
int distprev;

void setup() {
  myservo.attach(servo); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledWhite, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: "); // displays distance 
  Serial.print(distance);
  Serial.println(" cm");

  digitalWrite(ledWhite, HIGH); 

  if (distance <= 20 || distprev <= 20) {
    // lights
    digitalWrite(ledYellow, LOW); 
    digitalWrite(ledGreen, LOW);  

    // sound
    tone(speaker, 262, 1000 / 16);

    // motion
    myservo.write(20);
    digitalWrite(ledRed, HIGH); 
    digitalWrite(ledWhite, HIGH); 
    delay(40);
    myservo.write(0);
    digitalWrite(ledRed, LOW); 
    digitalWrite(ledWhite, LOW); 
    delay(40);


  } else if (distance <= 100 || distprev <= 100) {
    // lights
    digitalWrite(ledRed, LOW);  
    digitalWrite(ledYellow, HIGH); 
    digitalWrite(ledGreen, LOW);

    // motion
    myservo.write(90);
    delay(170);

  } else {
    // lights
    digitalWrite(ledRed, LOW); 
    digitalWrite(ledYellow, LOW);  
    digitalWrite(ledGreen, HIGH);  

    // motion
    if (myservo.read() < 180) {
      myservo.write(myservo.read() + 2);
    } else {
      myservo.write(180);
    }
    delay(50);
  }
  distprev = distance; // threashold, account for wrong readings sometimes
}
