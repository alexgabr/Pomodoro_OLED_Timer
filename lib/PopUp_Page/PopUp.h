#pragma once

#include <Arduino.h>

#include "Page.h"

class PopUp: public Page {
    private:
        // size
        uint8_t width, height;

        // content
        const char *message = "";

        // buttons
        uint8_t nrButtons = 0;
        struct {
            Button bttn;
            const char *bttn_name;
            uint8_t x, y; //coords for the text
        } button[32];

        uint8_t select = 0; // current selected button

        void clearWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void initWindow();
    public:
        PopUp(u8g2_t *display, uint8_t width, uint8_t height, const char *title = "", const char *message = "");
        PopUp(u8g2_t *display, uint8_t width, uint8_t height, uint8_t nrButtons, Button bttn_list[32], const char *bttn_names[32], uint8_t coords[32][2], const char *title = "", const char *message = "");

        void draw(const uint8_t *title_font, const uint8_t *content_font, void (*content)(void), bool title_is_centered = false);
        void draw(const uint8_t *title_font, const uint8_t *content_font, void (*content)(uint8_t), uint8_t option, bool title_is_centered = false);
        void draw(const uint8_t *title_font, const uint8_t *content_font, void (*content)(const char*), bool title_is_centered = false);

        void nextSelect();
        void prevSelect();

        void setMessage(const char *message);

        uint8_t getSelect();
        uint16_t getWidth();
        uint16_t getHeight();
};