#include "pages.h"

#include "Timerlib.h"
#include "Stopwatch.h"

extern Menu timerMenu;
extern Menu mainMenu;
extern Menu stopWatchMenu;
extern Menu settingsMenu;

extern Timer pomodoroTimer;
extern Stopwatch stopWatch;

void displayTimer(U8G2 &display, Gui &gui) {
    uint8_t minutes, seconds;

    display.firstPage();
    do {
        timerMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);

        pomodoroTimer.getFormattedTime(minutes, seconds);

        display.setCursor(50, 30);
        display.print(u8x8_u8toa(minutes, 2)); // TODO: daca minutes > 99 => u8x8_u8toa(minutes, 3)
        display.print(":");
        display.print(u8x8_u8toa(seconds, 2));
    } while(display.nextPage());
}

void displayStopWatch(U8G2 &display, Gui &gui) {
    uint16_t minutes;
    uint8_t seconds;

    display.firstPage();
    do {
        stopWatchMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);

        stopWatch.getFormattedTime(minutes, seconds);

        display.setCursor(50, 30);
        display.print(u8x8_u8toa(minutes, 2)); // TODO: daca minutes > 99 => u8x8_u8toa(minutes, 3)
        display.print(":");
        display.print(u8x8_u8toa(seconds, 2));
    } while(display.nextPage());
}

void displaySettings(U8G2 &display, Gui &gui) {
    // Implementare setări
}