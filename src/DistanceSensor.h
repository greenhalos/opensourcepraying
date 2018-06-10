#ifndef __DISTANCE_SENSOR_H__
#define __DISTANCE_SENSOR_H__

class DistanceSensor {
private:
  int triggerPin;
  int echoPin;

public:
  DistanceSensor (int triggerPin, int echoPin);
  long getDistance();
};

#endif
