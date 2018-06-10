#include "Player.h"

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

#define DEBUG false

int maximumVolume = 0;
int minimumVolume = 44;
int minimumDistance = 20;
int maximumDistance = 140;
double distanceToVolume = ((double)(minimumVolume - maximumVolume)) / ((double)(maximumDistance - minimumDistance));

Player::Player() {
  this->musicPlayer = new Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

  // initialise the music player
  if (! this->musicPlayer->begin()) { // initialise the music player
     Serial.println("Couldn't find VS1053, do you have the right pins defined?");
     while (1);
  }
  Serial.println("VS1053 found");

  this->musicPlayer->sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working

  if (!SD.begin(CARDCS)) {
    Serial.println("SD failed, or not present");
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");

  this->musicPlayer->setVolume(minimumVolume,minimumVolume);

  if (! this->musicPlayer->useInterrupt(VS1053_FILEPLAYER_PIN_INT)) {
    Serial.println("DREQ pin is not an interrupt pin");
  }
}


void Player::playWithSensors(const char* fileName, DistanceSensor* distanceSensor) {
  if (! this->musicPlayer->startPlayingFile(fileName)) {
    Serial.print("Could not open file ");
    Serial.println(fileName);
    while (1);
  }
  Serial.println("Started playing");

  while (this->musicPlayer->playingMusic) {
    int volume = convertToVolume(distanceSensor->getDistance());

    this->musicPlayer->setVolume(volume,volume);
    if (DEBUG) {
      Serial.print("Set volume to ");
      Serial.println(volume);
    }
    delay(100);
  }
}

int Player::convertToVolume(long distance) {
  int volume = (distance - minimumDistance) * distanceToVolume ;
  if (volume > minimumVolume) {
    volume = minimumVolume;
  }
  if (volume < maximumVolume) {
    volume = maximumVolume;
  }

  return volume;
}
