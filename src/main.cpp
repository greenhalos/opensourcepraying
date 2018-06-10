#include "DistanceSensor.h"
#include "Player.h"

DistanceSensor* sensor;


Player* musicPlayer;

void setup() {
  Serial.begin(9600);

  sensor = new DistanceSensor(A1, A2);

  musicPlayer = new Player();

}

void loop() {

  musicPlayer->playWithSensors("pray1.mp3", sensor);
}
