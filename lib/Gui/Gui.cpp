#include <Gui.h>

Gui::Gui(U8G2 &display, Menu &menu, uint8_t up, uint8_t down, uint8_t select) : display(display), menu(menu)
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
            menu.prevSelect();

            lastActivity = lastDebounceUp = now;
        }

        lastUpDetection = currentUp;
    }

    if(currentDown != lastDownDetection) {
        if(currentDown && now - lastDebounceDown >= BUTTON_DEBOUNCE) {
            menu.nextSelect();

            lastActivity = lastDebounceDown = now;
        }

        lastDownDetection = currentDown;
    }

    if(currentSelect != lastSelectDetection) {
        if(currentSelect && now - lastDebounceSelect >= BUTTON_DEBOUNCE) {
            currentOption = menu.getSelect();

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

        switch(currentOption)
            {
                case 0:
                    displayTimer(display);
                    break;
                case 1:
                    displayStopWatch(display);
                    break;
                case 2:
                    displaySettings(display);
                    break;
                default:
                     display.firstPage();
                     do {
                        menu.drawMenu(u8g2_font_ncenB08_tr, u8g2_font_5x8_tf, 1);
                    } while(display.nextPage());
            }
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
