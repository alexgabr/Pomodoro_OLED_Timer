#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

#include "Button.h"

class Page
{
    protected:
        const char *title;
        u8g2_t *display;

        uint8_t scroll_line = 0;
        
        void displayPageTitle(bool centered = false);
        void displayPageTitle(uint8_t pageWidth, uint8_t pageHeight, bool centered = false);
    public:
        Page(u8g2_t *display, const char *title = ""); // Constructor

        void setTitle(const char *title); // Set page title
        const char *getTitle(); // Get page title

        void scrollUp();
        void scrollDown();
};