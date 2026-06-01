#include "pages.h"

#include "Timerlib.h"
#include "Stopwatch.h"

extern Menu timerMenu;
extern Menu mainMenu;
extern Menu stopWatchMenu;
extern Menu settingsMenu;

extern PopUp one_button_alertPopUp;
extern PopUp two_buttons_alertPopUp;

extern Timer pomodoroTimer;
extern Stopwatch stopWatch;

void displayTimer(U8G2 &display, Gui &gui) {
    uint8_t minutes, seconds;

    timerMenu.drawMenu(DEFAULT_TITLE_FONT, DEFAULT_TEXT_FONT, true);

    pomodoroTimer.getFormattedTime(minutes, seconds);

    if(minutes < 100) {
        display.setCursor(50, 30);
        display.print(u8x8_u8toa(minutes, 2));
    }
    else {
        display.setCursor(45, 30);
        display.print(u8x8_u8toa(minutes, 3));
    }

    display.print(":");
    display.print(u8x8_u8toa(seconds, 2));

    if(minutes == 0 && seconds == 0) {
        one_button_alertPopUp.setMessage("Pomodoro Finalizat!!!");
        gui.showPopUp(&one_button_alertPopUp);
    }   
}

void displayStopWatch(U8G2 &display, Gui &gui) {
    uint16_t minutes;
    uint8_t seconds;

    stopWatchMenu.drawMenu(DEFAULT_TITLE_FONT, DEFAULT_TEXT_FONT, true);

    stopWatch.getFormattedTime(minutes, seconds);

    if(minutes < 100) {
        display.setCursor(50, 30);
        display.print(u8x8_u8toa(minutes, 2));
    }
    else {
        display.setCursor(45, 30);
        display.print(u8x8_u8toa(minutes, 3));
    }
    
    display.print(":");
    display.print(u8x8_u8toa(seconds, 2));
}

void displaySettings(U8G2 &display, Gui &gui) {
    settingsMenu.drawMenu(DEFAULT_TITLE_FONT, DEFAULT_TEXT_FONT, true);
}