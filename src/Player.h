#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include "DistanceSensor.h"

class Player {
private:
  Adafruit_VS1053_FilePlayer* musicPlayer;
  int convertToVolume(long distance);

public:
  Player();
  void playWithSensors(const char* fileName, DistanceSensor* distanceSensor);
};

#endif
