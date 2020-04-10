#include <Arduino.h>
#include <M5Stack.h>
#include <Grid.h>
//#include <Graph.h>
//#include "sensor.h"
#include "pnpmanager.h"
#include "screens.h"
#include "Free_Fonts.h"

#define SCREEN_MAIN 0
#define SCREEN_INSPECT 1
#define UPDATE_INTERVAL 1000

SensorManager manager;
// Grid mainGrid(&M5);
//Graph mainGraph(250, 200, &M5);
//int flag = 0;
int selectedSensor = 0;
int screen = SCREEN_MAIN;
uint64_t lastRefresh = 0;
int sensorCount = 0;

void setup() {
  //delay(5000);
  
  Serial.begin(115200);
  M5.begin();
  Serial.println("Starting manager..");
  manager.begin();
  M5.Lcd.clearDisplay();
  // mainGrid.begin();
  pinMode(36, INPUT); 
  //mainGraph.startGraph();
  Serial.println("Scan complete");
  M5.Lcd.setFreeFont(FSS12);
  sensorCount = manager.getSensorCount();
  if (!sensorCount) {
    sensor_not_found_screen(manager);
    while(!sensorCount) {
      manager.updateSensors();
      sensorCount = manager.getSensorCount();
      delay(1000);
    }
  }
  M5.Lcd.clearDisplay();
  sensor_list_screen(manager);
  draw_select_pointer(selectedSensor, sensorCount);
}

void loop() {
  M5.update();
  if (screen == SCREEN_MAIN) {
    if (M5.BtnC.wasPressed()) {
    selectedSensor ++;
    if (selectedSensor >= sensorCount ) selectedSensor = 0;
    draw_select_pointer(selectedSensor, sensorCount);
    }
    if (M5.BtnA.wasPressed()) {
      selectedSensor --;
      if (selectedSensor < 0 ) selectedSensor = sensorCount - 1;
      draw_select_pointer(selectedSensor, sensorCount);
    }
    if (M5.BtnB.wasPressed()) {
      manager.collect(selectedSensor);
      M5.Lcd.clearDisplay();
      screen = SCREEN_INSPECT;
      lastRefresh = millis() - 10000;
      return;
    }
  } else {
    // Update screen
    if (millis() - lastRefresh > UPDATE_INTERVAL) {
      M5.Lcd.clearDisplay();
      manager.collect(selectedSensor);
      draw_inspector(manager, selectedSensor);
      lastRefresh = millis();
    }
    if (M5.BtnB.wasPressed()) {
      M5.Lcd.clearDisplay();
      screen = SCREEN_MAIN;
      sensor_list_screen(manager);
      draw_select_pointer(selectedSensor, sensorCount);
    }
  }
  
  //mainGraph.updateGraph();
  //delay(200);
  // mainGrid.update();

  // manager.collect(0);
  // manager.interpretData(0);
  // delay(5000);
}
