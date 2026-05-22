#pragma once

#include "Arduino.h"
#include <U8g2lib.h>

#include "Page.h"
#include "Menu.h"
#include "defines.h"

class Gui {
    private:
        U8G2 &display;
        Menu *mainMenu;
        Menu *currentMenu;

        uint8_t pinUp;
        uint8_t pinDown;
        uint8_t pinSelect;

        uint8_t currentOption = 3; // default value is 3, which means that no option is selected

        bool lastUpDetection = 0;
        bool lastDownDetection = 0;
        bool lastSelectDetection = 0;

        uint32_t lastDebounceUp = 0;
        uint32_t lastDebounceDown = 0;
        uint32_t lastDebounceSelect = 0;

        uint32_t lastActivity = 0;

        void handleInput(); // handling user's input
        void render(); // rendering the content on display
    public:
        Gui(U8G2 &display, Menu *mainMenu, uint8_t up, uint8_t down, uint8_t select); // constructor

        void init(); // initialize gui once
        void update(); // loop update of the gui

        void changeMenu(Menu *newMenu); // change the current menu to a new one
        Menu *getMenu();
};