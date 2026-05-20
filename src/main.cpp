#include <Arduino.h>
#include <U8g2lib.h>

#include "Menu.h"

#include "defines.h"

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
uint8_t coords[3][2] = {{35, 30}, {35, 45}, {35, 60}};

Menu m(u8g2.getU8g2(), "Meniu", menu, button_name, coords, 3);

uint32_t last_press = 0;

bool last_button_state = 0;
uint32_t last_debounce_time = 0;

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    //OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); //25% brightness
    u8g2.setFont(u8g2_font_ncenB08_tr);

    pinMode(selectPin, INPUT_PULLDOWN);
}

void loop() {
    bool button_state = digitalRead(selectPin);
    if(button_state != last_button_state) {
        if(button_state && millis() - last_debounce_time >= BUTTON_DEBOUNCE) {
            m.nextSelect();

            last_debounce_time = last_press = millis();
        }

        last_button_state = button_state;
    }

    if(millis() - last_press >= INACTIVITY)
        u8g2.setPowerSave(1);
    else {
        u8g2.setPowerSave(0);

        //displaying the content
        u8g2.firstPage();
        do {
            m.drawMenu(u8g2_font_ncenB08_tr, u8g2_font_5x8_tf, 1);
        } while(u8g2.nextPage());
    }
}