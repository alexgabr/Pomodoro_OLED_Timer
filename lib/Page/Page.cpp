#include "Page.h"

#include "defines.h"

Page::Page(u8g2_t *display, const char *title)
{
    this->display = display;
    this->title = title;
}

void Page::displayPageTitle(bool centered)
{
    uint8_t x = 5;
    uint8_t y = u8g2_GetAscent(display) + 3 - scroll_line;

    if(centered)
        x = (u8g2_GetDisplayWidth(display) - u8g2_GetStrWidth(display, title)) / 2;

    u8g2_DrawStr(display, x, y, title);
}

void Page::displayPageTitle(uint8_t pageWidth, uint8_t pageHeight, bool centered)
{
    uint8_t x = (u8g2_GetDisplayWidth(display) - pageWidth) / 2 + 2;
    uint8_t y = u8g2_GetAscent(display) + (u8g2_GetDisplayHeight(display) - pageHeight) / 2 + 3 - scroll_line;

    if(centered)
        x += (pageWidth - u8g2_GetStrWidth(display, title)) / 2 - 2;

    u8g2_DrawStr(display, x, y, title);
}

void Page::activateScroll(bool turn_on)
{
    scroll_isActive = turn_on;
}

bool Page::scrollIsActive()
{
    return scroll_isActive;
}

void Page::setTitle(const char *title)
{
    this->title = title;
}

const char* Page::getTitle()
{
    return title;
}

void Page::scrollUp()
{
    scroll_line += DEFAULT_SCROLL;
}

void Page::scrollDown()
{
    if(scroll_line >= DEFAULT_SCROLL)
        scroll_line -= DEFAULT_SCROLL;
}