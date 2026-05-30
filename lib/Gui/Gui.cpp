#include "Gui.h"
#include "Timerlib.h"
#include "Stopwatch.h"

#include "pages.h"
#include "defines.h"
#include "content.h"

extern Menu timerMenu;
extern Menu mainMenu;
extern Menu stopWatchMenu;
extern Menu settingsMenu;

extern PopUp setValuePopUp;
extern PopUp alertPopUp;

extern Timer pomodoroTimer;
extern Stopwatch stopWatch;

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

    /* UP BUTTON */
    if (currentUp != lastUpDetection)
    {
        if (currentUp && now - lastDebounceUp >= BUTTON_DEBOUNCE && millis() - lastActivity < INACTIVITY)
        {
            if (isPopUpActive())
                activePopUp->prevSelect();
            else
                currentMenu->prevSelect();

            lastDebounceUp = now;
        }

        lastActivity = now;
        lastUpDetection = currentUp;
    }

    /* DOWN BUTTON */
    if (currentDown != lastDownDetection)
    {
        if (currentDown && now - lastDebounceDown >= BUTTON_DEBOUNCE && millis() - lastActivity < INACTIVITY)
        {
            if (isPopUpActive())
                activePopUp->nextSelect();
            else
                currentMenu->nextSelect();

            lastDebounceDown = now;
        }

        lastActivity = now;
        lastDownDetection = currentDown;
    }

    /* SELECT BUTTON */
    if (currentSelect != lastSelectDetection) {
        if (currentSelect && now - lastDebounceSelect >= BUTTON_DEBOUNCE && millis() - lastActivity < INACTIVITY) {
            uint8_t option;

            if (isPopUpActive()) {
                option = activePopUp->getSelect();

                /*prelucram optiunea selectata*/
            }   
            else {
                option = currentMenu->getSelect();

                if (currentMenu == &mainMenu)
                {
                    switch (option)
                    {
                    case 0:
                        changeMenu(&timerMenu); // BACK
                        break;
                    case 1:
                        changeMenu(&stopWatchMenu);
                        break;
                    case 2:
                        changeMenu(&settingsMenu);
                        break;
                    default:
                        break;
                    }
                }
                else if (currentMenu == &timerMenu)
                {
                    switch (option)
                    {
                    case 0:
                        changeMenu(&mainMenu); // BACK
                        break;
                    case 1:
                        if (pomodoroTimer.isRunning())
                            pomodoroTimer.stop();
                        else
                            pomodoroTimer.start();
                        break;
                    case 2:
                        pomodoroTimer.reset();
                        break;
                    default:
                        break;
                    }
                }
                else if (currentMenu == &stopWatchMenu)
                {
                    switch (option)
                    {
                    case 0:
                        changeMenu(&mainMenu); // BACK
                        break;
                    case 1:
                        if (stopWatch.isRunning())
                            stopWatch.stop();
                        else
                            stopWatch.start();
                        break;
                    case 2:
                        stopWatch.restart();
                        break;
                    default:
                        break;
                    }
                }
                else if (currentMenu == &settingsMenu)
                {
                }
            }

            lastDebounceSelect = now;
        }

        lastActivity = now;
        lastSelectDetection = currentSelect;
    }
}

void Gui::render()
{
    if (millis() - lastActivity >= INACTIVITY)
        display.setPowerSave(true);
    else
    {
        display.setPowerSave(false);

        display.firstPage();
        do
        {
            if (currentMenu == &mainMenu)
                mainMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);
            else if (currentMenu == &timerMenu)
                displayTimer(display, *this);
            else if (currentMenu == &stopWatchMenu)
                displayStopWatch(display, *this);
            // else if(currentMenu == &settingsMenu)
            // displaySettings(display, *this);

            if(isPopUpActive())
                activePopUp->draw(u8g2_font_profont12_mf, u8g2_font_tiny5_t_all, content_alert, true); //todo: trebuie selectata functia specifica fiecarui tip de popup
        } while (display.nextPage());
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

void Gui::showPopUp(PopUp *popUp)
{
    activePopUp = popUp;
}

void Gui::closePopUp()
{
    activePopUp = nullptr;
}

bool Gui::isPopUpActive()
{
    return activePopUp != nullptr;
}