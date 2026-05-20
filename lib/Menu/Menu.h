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
    public:
        Menu(u8g2_t *display, const char *title, Button list_bttns[32], const char *bttn_names[32], uint8_t coords[][2], uint8_t nrButtons);

        void drawMenu(bool title_is_centered = false);
        bool addButton(const char *name, Button button); // return 1 - successful; return 0 - error

        //TODO: setters for coords, name
        //TODO: bool deleteButton();
};