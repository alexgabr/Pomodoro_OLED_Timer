#include "content.h"

extern U8G2 u8g2; // the display

void content_changePomodoroDuration(uint8_t nr) {
    u8g2.setCursor(50, 35);
    u8g2.print(u8x8_u8toa(nr, 2));

    u8g2.setCursor(50, 43);
    u8g2.print("min");
}

void content_alert(const char *message) {
    u8g2.setCursor(30, 35);
    u8g2.print(message); // todo: optimizare pentru mesaje lungi
}