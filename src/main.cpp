#include <Arduino.h>
#include <U8g2lib.h>

#include "Page.h"

#define INACTIVITY 30000 // 30 seconds
const char *title = "Pomodoro";

//declaring the oled display in landscape mode
U8G2_SSD1309_128X64_NONAME0_1_HW_I2C u8g2(U8G2_R0);

Button btt(u8g2.getU8g2());

Button menu[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *button_name[3] = {"Timer", "StopWatch", "Settings"};

uint8_t bttn_selected = 0;
uint32_t last_press = 0;

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    //OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); //25% brightness
    u8g2.setFont(u8g2_font_ncenB08_tr);

    pinMode(17, INPUT_PULLDOWN);
}

void loop() {
    bool pressed = digitalRead(17);
    if(pressed)
        bttn_selected++,
        last_press = millis();

    if(millis() - last_press >= INACTIVITY)
        u8g2.setPowerSave(1);
    else{
        u8g2.setPowerSave(0);

        //displaying the content
        u8g2.firstPage();
        do {
            uint8_t x_title = (u8g2.getDisplayWidth() - u8g2.getStrWidth(title)) / 2;
            uint8_t y_title = u8g2.getAscent() + 3;

            u8g2.setCursor(x_title, y_title);
            u8g2.print(title);
        
           //btt.init(55, 35, "Button", pressed);
           for(int i = 0; i < 3; i++){
               uint8_t y_bttn = 32 + i * 13;
               menu[i].init(32, y_bttn, button_name[i], i == bttn_selected % 3);
           }
        } while(u8g2.nextPage());
    }

    delay(100);
}