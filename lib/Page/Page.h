#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

#include "Button.h"

class Page
{
    protected:
        char *title;
        u8g2_t *display;
    public:
        Page(u8g2_t *display, char *title = (char*)("")); // Constructor

        void setTitle(char *title); // Set page title
        char *getTitle(); // Get page title
};