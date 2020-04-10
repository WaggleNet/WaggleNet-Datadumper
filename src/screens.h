#include <Arduino.h>
#include <M5Stack.h>
#include "pnpmanager.h"

void sensor_not_found_screen(SensorManager& manager);
void sensor_list_screen(SensorManager& manager);
void draw_select_pointer(int selected, int total);
void draw_inspector(SensorManager& manager, int selected);
