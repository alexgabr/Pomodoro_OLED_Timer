#include "Menu.h"

Menu::Menu(u8g2_t *display, char *title, Button list_bttns[], char *bttn_names[], uint8_t nrButtons) : Page(display, title)
{
    this->nrButtons = nrButtons;

    for(int i = 0; i < nrButtons; i++){
        button[i].bttn = list_bttns[i];
        button[i].bttn_name = bttn_names[i];
    }
}