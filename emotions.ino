//www.elegoo.com

//2018.10.25

/*
  Zoé Caudron
  Optimistic Plant
  (Conveying an emotion: optimism)
  Optimism reminds me of a glass half-full. And what else loves a half glass of water?
  That's right, plants do. While it would be interesting to have the plant react to
  data or world news, for now it's just happy to see you. Being in good company makes
  the future look brighter!

  Uses an Ultrasonic sensor, a stepper motor and a LED

*/

#include <Stepper.h>
#include "SR04.h"
#define TRIG_PIN 13
#define ECHO_PIN 12

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
const int pinB = 7;
long a;
int step = 0;
float count = 0;

void setup() {
  myStepper.setSpeed(15);
  pinMode(pinB, OUTPUT);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {



  a = sr04.Distance();
  delay(100);

  if (a <= 50) {      // if I'm close to the sensor, increment count
    count += 0.5;
  }
  else {
    count = 0;        // if I'm away, stay at 0
  }

  if (count >= 30) {  // if I've been there long enough, the blue LED lights up: glass half-full!
    digitalWrite(pinB, HIGH);
  }
  else {
    digitalWrite(pinB, LOW);
  }

  if (digitalRead(pinB) == HIGH) {    // and if there's water, the plants can grow
    myStepper.step(step);

    step += 1000;
  }



}
