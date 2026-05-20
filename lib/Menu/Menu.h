#pragma once

#include "Page.h"

class Menu: public Page{
    private:
        uint8_t nrButtons = 0;
        struct{
            Button bttn;
            const char *bttn_name;
            uint8_t x, y; //coords for the text
        } button[32];

        uint8_t select = 0; //number of times select button was pressed
    public:
        Menu(u8g2_t *display, const char *title, Button list_bttns[32], const char *bttn_names[32], uint8_t coords[32][2], uint8_t nrButtons);

        void nextSelect();
        void drawMenu(const uint8_t *title_font, const uint8_t *content_font, bool title_is_centered = false);
        bool addButton(Button button, const char *name, uint8_t x_text, uint8_t y_text); // return 1 - successful; return 0 - error

        //TODO: setters for coords, name
        //TODO: bool deleteButton();
};