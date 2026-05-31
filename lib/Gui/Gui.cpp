#include "Gui.h"
#include "Timerlib.h"
#include "Stopwatch.h"

#include "pages.h"
#include "content.h"

extern Menu timerMenu;
extern Menu mainMenu;
extern Menu stopWatchMenu;
extern Menu settingsMenu;

extern PopUp setValuePopUp;
extern PopUp one_button_alertPopUp;
extern PopUp two_buttons_alertPopUp;

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

                if(activePopUp == &one_button_alertPopUp)
                    closePopUp();
                else if(activePopUp == &two_buttons_alertPopUp) {
                    if(currentMenu == &stopWatchMenu)
                        switch(option) {
                            case 0:
                                closePopUp();
                                stopWatch.start();
                                break;
                            case 1:
                                closePopUp();
                                stopWatch.restart();
                        }
                }
                else if(activePopUp == &setValuePopUp) {
                    switch (option) {
                        case 0:
                            if(value > MIN_POMODORO_TIME)
                                value--;
                            break;
                        case 1:
                            value++;
                            break;
                        case 2:
                            pomodoro_time = value;
                            pomodoroTimer.setPomodoroLength(pomodoro_time);
                            
                            closePopUp();
                            break;
                    }
                }
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
                    switch (option) {
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
                    switch (option) {
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
                        if(stopWatch.isRunning()) {
                            stopWatch.stop();

                            two_buttons_alertPopUp.setMessage("Do you want to restart\nthe timer?");
                            showPopUp(&two_buttons_alertPopUp);
                        }
                        break;
                    default:
                        break;
                    }
                }
                else if (currentMenu == &settingsMenu) {
                    switch(option) {
                        case 0:
                            changeMenu(&mainMenu);
                            break;
                        case 1:
                            value = pomodoro_time;

                            setValuePopUp.setTitle("Change value");
                            showPopUp(&setValuePopUp);
                            break;
                        case 2:
                            break;
                    }
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
    display.firstPage();
    do {
        if (currentMenu == &mainMenu)
            mainMenu.drawMenu(u8g2_font_profont12_mf, u8g2_font_profont10_mf, true);
        else if (currentMenu == &timerMenu)
            displayTimer(display, *this);
        else if (currentMenu == &stopWatchMenu)
            displayStopWatch(display, *this);
        else if(currentMenu == &settingsMenu)
            displaySettings(display, *this);

        if(isPopUpActive()) {
            if(activePopUp == &one_button_alertPopUp)
                activePopUp->draw(u8g2_font_profont12_mf, u8g2_font_tiny5_t_all, content_alert, true);
            else if(activePopUp == &two_buttons_alertPopUp)
                activePopUp->draw(u8g2_font_profont12_mf, u8g2_font_tiny5_t_all, content_alert, true);
            else if(activePopUp == &setValuePopUp)
                activePopUp->draw(u8g2_font_profont12_mf, u8g2_font_tiny5_t_all, content_changePomodoroDuration, value, true);
        }
            
    } while(display.nextPage());

    if (millis() - lastActivity >= INACTIVITY && !isPopUpActive())
        display.setPowerSave(true);
    else
        display.setPowerSave(false);
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