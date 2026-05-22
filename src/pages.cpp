#include "pages.h"

#include "Button.h"
#include "Menu.h"
#include "Gui.h"

extern Menu timerMenu;

void displayTimer(U8G2 &display, Gui &gui) {
    if(gui.getMenu() != &timerMenu)
        gui.changeMenu(&timerMenu);

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