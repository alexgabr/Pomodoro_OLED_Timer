#include "pages.h"

extern Menu timerMenu;
extern Menu mainMenu;
// extern Menu stopWatchMenu;
// extern Menu settingsMenu;

void displayTimer(U8G2 &display, Gui &gui) {
    display.firstPage();
    do {
        timerMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);

        display.drawStr(45, 30, "25:00");
    } while(display.nextPage());
}

void displayStopWatch(U8G2 &display, Gui &gui) {
    // Implementare stopwatch
}

void displaySettings(U8G2 &display, Gui &gui) {
    // Implementare setări
}