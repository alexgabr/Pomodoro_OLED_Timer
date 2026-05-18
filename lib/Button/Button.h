#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

class Button{
    private:
        u8g2_t *display;
        struct
        {
            uint8_t width, height;
        } bttn_size;
    public:
        //constructor
        Button(u8g2_t *display, uint8_t width = 0, uint8_t height = 0);

        //functions
        void init(uint8_t x_text, uint8_t y_text, const char *text, bool is_inverted = false);

        //setters and getters
        void setSize(uint8_t width, uint8_t height);
        uint8_t getWidth();
        uint8_t getHeight();
};