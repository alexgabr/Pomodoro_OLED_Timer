#pragma once

#include "Arduino.h"
#include <U8g2lib.h>

#include "Page.h"
#include "Menu.h"
#include "defines.h"

#include "pages.h"

class Gui {
    private:
        U8G2 &display;
        Menu &menu;

        uint8_t pinUp;
        uint8_t pinDown;
        uint8_t pinSelect;

        enum Option {
            TIMER,
            STOPWATCH,
            SETTINGS,
            BACK
        } currentOption;

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
        Gui(U8G2 &display, Menu &menu, uint8_t up, uint8_t down, uint8_t select); // constructor

        void init(); // initialize gui once
        void update(); // loop update of the gui
};