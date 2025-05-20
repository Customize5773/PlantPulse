#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <Arduino.h>

#define SOIL_PIN 34 // Change as needed for ESP32

int readSoilMoisture() {
  int raw = analogRead(SOIL_PIN);
  int moisturePercent = map(raw, 4095, 1200, 0, 100); // Adjust with calibration
  return moisturePercent;
}

#endif
