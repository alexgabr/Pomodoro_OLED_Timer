#pragma once

#include <Arduino.h>

#include "Page.h"

class PopUp: public Page {
    private:
        // size
        uint8_t width, height;

        // buttons
        uint8_t nrButtons = 0;
        struct {
            Button bttn;
            const char *bttn_name;
            uint8_t x, y; //coords for the text
        } button[32];
    public:
        PopUp(u8g2_t *display, uint8_t width, uint8_t height, const char *title = "");
        PopUp(u8g2_t *display, uint8_t width, uint8_t height, uint8_t nrButtons, Button bttn_list[32], const char *bttn_names[32], uint8_t coords[32][2], const char *title = "");

        void draw(const uint8_t *title_font, const uint8_t *content_font, bool title_is_centered);

        uint16_t getWidth();
        uint16_t getHeight();
};