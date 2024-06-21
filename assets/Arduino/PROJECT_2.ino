/*
Main code of the interactive object.
*/
#include <Servo.h>
#include "pitches.h"

Servo myservoL; 
Servo myservoR;

int echoPinIn = 4; 
int trigPinIn = 5;
int echoPinOut = 2; 
int trigPinOut = 3;

int ledRedL = 8;
int ledBlueL = 9;
int ledRedR = 10;
int ledBlueR = 7;

int servoL = 6;
int servoR = 11;

int buzzer = 13;

long durationIn;
long durationOut;
int distanceIn;
int distanceOut;

int i;

// music
int bugu[] = {
  NOTE_C2, NOTE_C6, NOTE_G5, REST, NOTE_C2, NOTE_C6, NOTE_G5, REST
};

int tempo = 144;

int buguDurations[] = {
  6, 1.3, 3, 2, 6, 1.3, 3, 2
};

bool playBugu;

void setup() {
  pinMode(trigPinIn, OUTPUT); 
  pinMode(echoPinIn, INPUT); 
  pinMode(trigPinOut, OUTPUT); 
  pinMode(echoPinOut, INPUT); 

  myservoL.attach(servoL); 
  myservoR.attach(servoR); 

  pinMode(ledRedL, OUTPUT);
  pinMode(ledRedR, OUTPUT);
  pinMode(ledBlueL, OUTPUT);
  pinMode(ledBlueR, OUTPUT);

  Serial.begin(9600);

  playBugu = true;
}

void loop() {
  // Get distance from Outer
  digitalWrite(trigPinOut, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPinOut, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinOut, LOW);

  durationOut = pulseIn(echoPinOut, HIGH);
  distanceOut = durationOut * 0.034 / 2;
  
  Serial.print("Distance: "); // displays distance 
  Serial.print(distanceOut);
  Serial.println("outer cm");

  // default lights
  digitalWrite(ledRedL, HIGH);
  digitalWrite(ledRedR, HIGH);

  // Default: Outer far, inner close

  // When outer close
  if (distanceOut <= 100) {

    // open door
    if (myservoL.read() > 10) {
      myservoL.write(myservoL.read() - 2);
      myservoR.write(myservoR.read() + 2);
      delay(10);
      playBugu = true;
    } else {
      myservoL.write(10);
      myservoR.write(170);

      if (playBugu == true) {
        
        delay(500);

        // open lights
        digitalWrite(ledBlueL, HIGH);
        digitalWrite(ledBlueR, HIGH);
        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int buguDuration = 1000 / buguDurations[thisNote];
          tone(buzzer, bugu[thisNote], buguDuration);
          int pauseBetweenNotes = buguDurations;
          delay(pauseBetweenNotes);
          noTone(buzzer);

          // long longer play sound
          playBugu = false;

        }
        delay(1000);
      }

      // Get distance from Inner
      digitalWrite(trigPinIn, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPinIn, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPinIn, LOW);

      durationIn = pulseIn(echoPinIn, HIGH);
      distanceIn = durationIn * 0.034 / 2;
      
      Serial.print("Distance: "); // displays distance 
      Serial.print(distanceIn);
      Serial.println("inner cm");

      if (distanceIn > 10) {
        digitalWrite(ledBlueR, LOW);
        digitalWrite(ledBlueL, LOW);

        for (int thisNote = 0; thisNote < 8; thisNote++) {
          int buguDuration = 2000 / buguDurations[thisNote];
          tone(buzzer, bugu[thisNote] * 0.5, buguDuration * 2);
          int pauseBetweenNotes = buguDurations + 100;
          delay(pauseBetweenNotes);
          noTone(buzzer);

        }
      }
    }
  } else {
    // close door
    if (myservoL.read() < 170) {
      myservoL.write(myservoL.read() + 2);
      myservoR.write(myservoR.read() - 2);
      delay(10);
    } else {
      myservoL.write(170);
      myservoR.write(10);
      digitalWrite(ledBlueR, LOW);
      digitalWrite(ledBlueL, LOW);
    }
  }
}