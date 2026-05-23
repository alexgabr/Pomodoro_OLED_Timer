#include <Gui.h>

#include "pages.h"

extern Menu timerMenu;
extern Menu mainMenu;
// extern Menu stopWatchMenu;
// extern Menu settingsMenu;

Gui::Gui(U8G2 &display, Menu *homeMenu, uint8_t up, uint8_t down, uint8_t select) : display(display), homeMenu(homeMenu), currentMenu(homeMenu)
{
    pinUp = up;
    pinDown = down;
    pinSelect = select;
}

/* PRIVATE FUNCTIONS */

void Gui::handleInput()
{
    bool currentUp = digitalRead(pinUp);
    bool currentDown = digitalRead(pinDown);
    bool currentSelect = digitalRead(pinSelect);

    uint32_t now = millis();

    if(currentUp != lastUpDetection) {
        if(currentUp && now - lastDebounceUp >= BUTTON_DEBOUNCE) {
            currentMenu->prevSelect();

            lastActivity = lastDebounceUp = now;
        }

        lastUpDetection = currentUp;
    }

    if(currentDown != lastDownDetection) {
        if(currentDown && now - lastDebounceDown >= BUTTON_DEBOUNCE) {
            currentMenu->nextSelect();

            lastActivity = lastDebounceDown = now;
        }

        lastDownDetection = currentDown;
    }

    if(currentSelect != lastSelectDetection) {
        if(currentSelect && now - lastDebounceSelect >= BUTTON_DEBOUNCE) {
            uint8_t option = currentMenu->getSelect();

            if(currentMenu == &mainMenu) {
                switch(option) {
                    case 0:
                        changeMenu(&timerMenu); // BACK
                        break;
                    case 1:
                        //changeMenu(&stopWatchMenu);
                        break;
                    case 2:
                       // changeMenu(&settingsMenu);
                        break;
                    default:
                        break;
                }
            }
            else if(currentMenu == &timerMenu) {
                switch(option) {
                    case 0:
                        changeMenu(&mainMenu); // BACK
                        break;
                    case 1:
                        // start timer
                        break;
                    case 2:
                        // reset timer
                        break;
                    default:
                        break;
                }
            }
            // else if(currentMenu == &stopWatchMenu) {}
            // else if(currentMenu == &settingsMenu) {}

            lastActivity = lastDebounceSelect = now;
        }
        lastSelectDetection = currentSelect;
    }
}

void Gui::render()
{
    if(millis() - lastActivity >= INACTIVITY)
        display.setPowerSave(true);
    else {
        display.setPowerSave(false);

        display.firstPage();
        do {
            if(currentMenu == &mainMenu)
                mainMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);
            else if(currentMenu == &timerMenu)
                displayTimer(display, *this);
            //else if(currentMenu == &stopWatchMenu)
            //else if(currentMenu == &settingsMenu)
        } while(display.nextPage());
    }
}

/* PUBLIC FUNCTIONS */

void Gui::init()
{
    pinMode(pinUp, INPUT_PULLDOWN);
    pinMode(pinDown, INPUT_PULLDOWN);
    pinMode(pinSelect, INPUT_PULLDOWN);

    lastActivity = millis();
}

void Gui::update()
{
    handleInput();
    render();
}

void Gui::changeMenu(Menu *newMenu)
{
    currentMenu = newMenu;
}

Menu *Gui::getMenu()
{
    return currentMenu;
}