#include <Servo.h>

Servo lifterServo;  // continuous rotation servo that lifts the page
Servo flipperServo;  // 180 degree servo that flips the page

const int thresholdValue = 270;
const int sensorPin = A0;    // EMG signal input pin

int sensorValue = 0;  // store EMG signal sensor value
int pos = 0;  // store position of Flipper

void setup() {
  flipperServo.attach(9);
  flipperServo.write(180);  // initialize Flipper to face right (180 degrees)
  flipperServo.detach();

  lifterServo.attach(11);
  lifterServo.detach();

  Serial.begin(9600);
}

void loop() {

  // read the value from the sensor
  sensorValue = analogRead(sensorPin);

  Serial.print(0);
  Serial.print(" ");
  Serial.print(820);
  Serial.print(" ");
  Serial.println(sensorValue);

  // trigger motors if thresholdValue exceeded
  if (sensorValue > thresholdValue) {

    ////////////
    // LIFTER //
    ////////////

    lifterServo.attach(11);

    lifterServo.write(90);  // rotate clockwise
    delay(5000);  // hold for 5 seconds as page lifts
    lifterServo.write(92);  // return to stationary

    lifterServo.detach();

    /////////////
    // FLIPPER //
    /////////////

    flipperServo.attach(9);

    // turn counterclockwise from 180 degrees to 0 degrees
    for (pos = 180; pos >= 0; pos -= 1) {
      flipperServo.write(pos);
      delay(5);  // 5 ms pause between each position to decrease speed of turn
    }

    delay(1500);  // wait a moment before returning to starting position

    // turn clockwise from 0 degrees to 180 degrees
    for (pos = 0; pos <= 180; pos += 1) {
      // in steps of 1 degree
      flipperServo.write(pos);
      delay(10);  // 10 ms pause in between each position
    }

    flipperServo.detach();

    delay(1000);
  }
}