#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1309_128X64_NONAME0_1_HW_I2C u8g2(U8G2_R0);

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    //OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(150);
    u8g2.setFont(u8g2_font_ncenB08_tr);
}

void loop() {
    uint8_t x_title = (u8g2.getDisplayWidth() - u8g2.getStrWidth("Timer")) / 2;
    uint8_t y_title = u8g2.getAscent() + 3;

    u8g2.firstPage();
    do {
        u8g2.setCursor(x_title, y_title);
        u8g2.print(F("Timer"));
    } while(u8g2.nextPage());

    //delay(1000);
}