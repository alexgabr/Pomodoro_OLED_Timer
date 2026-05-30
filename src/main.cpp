#include <Arduino.h>
#include <U8g2lib.h>

#include "defines.h"

#include "Gui.h"

#include "Timerlib.h"
#include "Stopwatch.h"

int pomodoro_time = DEFAULT_POMODORO_TIME;

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

// ----- Settings menu declaration -----
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
Timer pomodoroTimer(pomodoro_time * 60 * 1000); 

// ----- Stopwatch declaration -----
Stopwatch stopWatch;

// POPUP TEST
#include "PopUp.h"
#include "bitmaps.h"

Button popupButtons[3] = {
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2()),
    Button(u8g2.getU8g2())
};

const char *popup_button_name[] = {"+", "-", "Ok"};
uint8_t popup_coords[3][2] = {{28, 35}, {94, 35}, {60, 50}};
PopUp p(u8g2.getU8g2(), 90, 55, 3, popupButtons, popup_button_name, popup_coords, "Test");

void setup() {
    Serial.begin(115200);

    while(!Serial);
    Serial.print("Serial comms on!\n\n");

    // OLED Display initialization
    u8g2.begin();
    u8g2.setContrast(64); // 25% brightness
    u8g2.setFont(u8g2_font_ncenB08_tr);

    gui.init();
}

void loop() {
    //gui.update();
    bool ok = digitalRead(selectButton);

    u8g2.firstPage();
    do {
        u8g2.setCursor(15, 30);
        u8g2.print("Acesta este un test");

        if(ok) {
            p.draw(u8g2_font_profont12_mf, u8g2_font_tiny5_t_all, true);
        }
    } while(u8g2.nextPage());
}