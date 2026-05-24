#include <Arduino.h>
#include <U8g2lib.h>

#include "Gui.h"

#include "Timerlib.h"
#include "Stopwatch.h"

#include "defines.h"

// declaring the oled display in landscape mode
U8G2_SSD1309_128X64_NONAME0_1_HW_I2C u8g2(U8G2_R0);

// ----- Main menu declaration -----
Button mainMenu_buttons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *mainMenu_button_name[] = {"Timer", "StopWatch", "Settings"};
uint8_t coords[3][2] = {{35, 30}, {35, 45}, {35, 60}};
Menu mainMenu(u8g2.getU8g2(), "Meniu", mainMenu_buttons, mainMenu_button_name, coords, 3);

// ----- Timer menu declaration -----
Button timerButtons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *timer_button_name[] = {"Back", "Start/Stop", "Reset"}; 
uint8_t timer_coords[3][2] = {{5, 20}, {15, 60}, {80, 60}};
Menu timerMenu(u8g2.getU8g2(), "Timer", timerButtons, timer_button_name, timer_coords, 3);

// ----- StopWatch menu declaration -----
Button stopWatchButtons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *stopWatch_button_name[] = {"Back", "Start/Stop", "Reset"}; 
uint8_t stopWatch_coords[3][2] = {{5, 20}, {15, 60}, {80, 60}};
Menu stopWatchMenu(u8g2.getU8g2(), "StopWatch", stopWatchButtons, stopWatch_button_name, stopWatch_coords, 3);

// ----- StopWatch menu declaration -----
Button settingsButtons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *settings_button_name[] = {"", "", ""};
uint8_t settings_coords[3][2] = {{5, 20}, {15, 60}, {80, 60}};
Menu settingsMenu(u8g2.getU8g2(), "Settings", settingsButtons, settings_button_name, settings_coords, 3);

// ----- Gui declaration -----
Gui gui(u8g2, &mainMenu, upButton, downButton, selectButton);

// ----- Timer declaration -----
Timer pomodoroTimer(25 * 60 * 1000);

// ----- Stopwatch declaration -----
Stopwatch stopWatch;

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    // OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); // 25% brightness

    gui.init();
}

void loop() {
    gui.update();
}