#include "Page.h"

Page::Page(u8g2_t *display, const char *title)
{
    this->display = display;
    this->title = title;
}

void Page::displayPageTitle(bool centered)
{
    uint8_t x = 5;
    uint8_t y = u8g2_GetAscent(display) + 3;

    if(centered)
        x = (u8g2_GetDisplayWidth(display) - u8g2_GetStrWidth(display, title)) / 2;

    u8g2_DrawStr(display, x, y, title);
}

void Page::setTitle(const char *title)
{
    this->title = title;
}

const char* Page::getTitle()
{
    return title;
}