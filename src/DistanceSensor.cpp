#include <Arduino.h>

#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int triggerPin, int echoPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


long DistanceSensor::getDistance() {
  digitalWrite(this->triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->triggerPin, LOW);
  long duration = pulseIn(this->echoPin, HIGH);
  return (duration / 2) / 29.1;
}
