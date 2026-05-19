#pragma once

#include "Page.h"

class Menu: public Page{
    private:
        uint8_t nrButtons = 0;
        struct{
            Button bttn;
            char *bttn_name;
        } button[32];
    public:
        Menu(u8g2_t *display, char *title = "", Button list_bttns[], char *bttn_names[], uint8_t nrButtons);

        void drawMenu(); //todo: parameters
        void addButton(char *name, Button button);
};