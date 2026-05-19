#include "Menu.h"

Menu::Menu(u8g2_t *display, const char *title, Button list_bttns[], const char *bttn_names[], uint8_t coords[][2], uint8_t nrButtons) : Page(display, title)
{
    this->nrButtons = nrButtons;

    for(int i = 0; i < nrButtons; i++){
        button[i].bttn = list_bttns[i];
        button[i].bttn_name = bttn_names[i];

        button[i].x = coords[i][0];
        button[i].y = coords[i][1];
    }
}

void Menu::drawMenu()
{
    //TODO: display page title

    for(int i = 0; i < nrButtons; i++){
        button[i].bttn.init(button[i].x, button[i].y, button[i].bttn_name);
    }
}