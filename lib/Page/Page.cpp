#include "Page.h"

Page::Page(u8g2_t *display, const char *title)
{
    this->display = display;
    this->title = title;
}

void Page::setTitle(const char *title)
{
    this->title = title;
}

const char* Page::getTitle()
{
    return title;
}