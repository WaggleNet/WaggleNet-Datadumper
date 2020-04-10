#include "screens.h"
#include "Free_Fonts.h"

void sensor_not_found_screen(SensorManager& manager) {
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setFreeFont(FSS12);
    M5.Lcd.drawString("Smart Sensor inspect", 20, 30);
    M5.Lcd.setFreeFont(FSS18);
    M5.Lcd.setTextColor(YELLOW, BLACK);
    M5.Lcd.drawString("Sensor not found", 20, 70);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setFreeFont(FSS12);
    M5.Lcd.drawString("Plug in the sensor now..", 20, 120);
}

void sensor_list_screen(SensorManager& manager) {
    M5.Lcd.setTextColor(CYAN, BLACK);
    M5.Lcd.drawString("Addr", 20, 20);
    M5.Lcd.drawString("Type", 90, 20);
    M5.Lcd.drawString("#entries", 200, 20);
    for (int i = 0; i < manager.getSensorCount(); i++) {
        int y = 50 + 24*i;
        auto& sensor = *(manager.getSensor(i));
        M5.Lcd.setTextColor(WHITE, BLACK);
        M5.Lcd.drawString(String("0x")+String(sensor.address, HEX), 20, y);
        M5.Lcd.drawString(String("0x")+String(sensor.type, HEX), 90, y);
        M5.Lcd.drawString(String(sensor.getSize()), 200, y);
    }
}

void draw_select_pointer(int selected, int total) {
    M5.Lcd.setTextColor(ORANGE, BLACK);
    M5.Lcd.fillRect(0, 0, 20, 240, ILI9341_BLACK);
    M5.Lcd.drawString(">", 5, 50+24*selected);
    M5.Lcd.setTextColor(WHITE, BLACK);
}

void draw_inspector(SensorManager& manager, int selected) {
    // Draw sensor header
    M5.Lcd.setTextColor(CYAN, BLACK);
    M5.Lcd.drawString("Addr", 20, 20);
    M5.Lcd.drawString("Type", 20, 44);
    M5.Lcd.setTextColor(WHITE, BLACK);
    auto& sensor = *(manager.getSensor(selected));
    M5.Lcd.drawString(String("0x")+String(sensor.address, HEX), 90, 20);
    M5.Lcd.drawString(String("0x")+String(sensor.type, HEX), 90, 44);
    // Draw table header
    M5.Lcd.setTextColor(CYAN, BLACK);
    M5.Lcd.drawString("#", 20, 80);
    M5.Lcd.drawString("size", 60, 80);
    M5.Lcd.drawString("data", 120, 80);
    M5.Lcd.setTextColor(WHITE, BLACK);
    for (int i = 0; i < sensor.getSize(); i++) {
        int y = 106 + 24*i;
        M5.Lcd.drawString(String(i), 20, y);
        M5.Lcd.drawString(String(sensor.getLength(i)), 60, y);
        String s = "";
        uint8_t* buf = (uint8_t*)sensor.getData(i);
        for (int j = 0; j < sensor.getLength(i); j++) {
            s += String(buf[j], HEX);
            s += " ";
        }
        M5.Lcd.drawString(s, 120, y);
    }
}
