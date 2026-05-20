#include "Menu.h"

Menu::Menu(u8g2_t *display, const char *title, Button list_bttns[32], const char *bttn_names[32], uint8_t coords[32][2], uint8_t nrButtons) : Page(display, title)
{
    this->nrButtons = nrButtons;

    for(int i = 0; i < nrButtons; i++){
        button[i].bttn = list_bttns[i];
        button[i].bttn_name = bttn_names[i];

        button[i].x = coords[i][0];
        button[i].y = coords[i][1];
    }
}

void Menu::drawMenu(bool title_is_centered) //todo: add fonts for title and the contents
{   
    displayPageTitle(title_is_centered);

    for(int i = 0; i < nrButtons; i++){
        button[i].bttn.init(button[i].x, button[i].y, button[i].bttn_name, i == select % nrButtons);
    }
}

void Menu::nextSelect()
{
    select++;
}

bool Menu::addButton(Button button, const char *name, uint8_t x_text, uint8_t y_text)
{
    if(nrButtons >= 31) // max is 32 buttons; first index is 0
        return 0;

    nrButtons++;

    this->button[nrButtons].bttn = button;
    this->button[nrButtons].bttn_name = name;
    this->button[nrButtons].x = x_text;
    this->button[nrButtons].y = y_text;

    return 1;
}