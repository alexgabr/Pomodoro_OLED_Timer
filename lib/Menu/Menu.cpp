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

void Menu::drawMenu(const uint8_t *title_font, const uint8_t *content_font, bool title_is_centered)
{   
    u8g2_SetFont(display, title_font);
    displayPageTitle(title_is_centered);

    u8g2_SetFont(display, content_font);
    for(int i = 0; i < nrButtons; i++){
        button[i].bttn.init(button[i].x, button[i].y, button[i].bttn_name, i == select % nrButtons);
    }
}

void Menu::nextSelect()
{
    select++;
}

void Menu::prevSelect()
{
    if(select == 0)
        select = nrButtons - 1;
    else
        select--;
}

uint8_t Menu::getSelect()
{
    return select % nrButtons;
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