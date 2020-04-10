#include <Arduino.h>
#include "sensor.h"
#include "pnpmanager.h"

SensorManager manager;

void setup() {
  Serial.begin(115200);
  manager.begin();
  Serial.println("Scan complete");
}

void loop() {
  manager.collect(0);
  manager.dumpToSerial(0);
  delay(5000);
}
