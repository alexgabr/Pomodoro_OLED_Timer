#include <Arduino.h>
#include <U8g2lib.h>

#include "Button.h"
#include "Menu.h"
#include "Gui.h"

#include "Timerlib.h"

#include "defines.h"

//declaring the oled display in landscape mode
U8G2_SSD1309_128X64_NONAME0_1_HW_I2C u8g2(U8G2_R0);

// Main menu declaration
Button mainMenu_buttons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *mainMenu_button_name[3] = {"Timer", "StopWatch", "Settings"};
uint8_t coords[3][2] = {{35, 30}, {35, 45}, {35, 60}};
Menu mainMenu(u8g2.getU8g2(), "Meniu", mainMenu_buttons, mainMenu_button_name, coords, 3);

// Timer menu declaration
Button timerButtons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *timer_button_name[3] = {"Back", "Start", "Reset"}; 
uint8_t timer_coords[3][2] = {{5, 20}, {30, 60}, {80, 60}};
Menu timerMenu(u8g2.getU8g2(), "Timer", timerButtons, timer_button_name, timer_coords, 3);

// Gui declaration
Gui gui(u8g2, &mainMenu, upButton, downButton, selectButton);

// Timer declaration
Timer pomodoroTimer(25 * 60 * 1000);

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    //OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); //25% brightness

    gui.init();
}

void loop() {
    gui.update();
}