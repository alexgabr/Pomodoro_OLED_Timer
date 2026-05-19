#include "Page.h"

Page::Page(u8g2_t *display, char *title)
{
    this->display = display;
    this->title = title;
}

void Page::setTitle(char *title)
{
    this->title = title;
}

char* Page::getTitle()
{
    return title;
}