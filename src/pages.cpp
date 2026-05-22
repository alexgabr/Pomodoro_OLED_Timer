#include "pages.h"

#include "Button.h"
#include "Menu.h"

void displayTimer(U8G2 &display) {
    const char *button_name[3] = {"Back", "Start", "Reset"}; 
    uint8_t coords[3][2] = {{10, 20}, {30, 60}, {80, 60}};

    Button timerButtons[3] = {
        Button(display.getU8g2()),
        Button(display.getU8g2()),
        Button(display.getU8g2())
    };

    Menu timerMenu(display.getU8g2(), "Timer", timerButtons, button_name, coords, 3);

    display.firstPage();
    do {
        timerMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);

        display.drawStr(45, 30, "25:00");
    } while(display.nextPage());
}

void displayStopWatch(U8G2 &display) {
    // Implementare stopwatch
}

void displaySettings(U8G2 &display) {
    // Implementare setări
}