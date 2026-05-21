#include <Arduino.h>
#include <U8g2lib.h>

#include "Button.h"
#include "Menu.h"
#include "Gui.h"

#include "defines.h"

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

Gui gui(u8g2, m, upButton, downButton, selectButton);

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    //OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); //25% brightness
    u8g2.setFont(u8g2_font_ncenB08_tr);

    gui.init();
}

void loop() {
    gui.update();
}