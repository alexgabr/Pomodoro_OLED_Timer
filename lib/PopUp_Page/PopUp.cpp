#include "PopUp.h"

PopUp::PopUp(u8g2_t *display, uint8_t width, uint8_t height, const char *title) : Page(display, title)
{
    this->width = width;
    this->height = height;
}

PopUp::PopUp(u8g2_t *display, uint8_t width, uint8_t height, uint8_t nrButtons, Button bttn_list[32], const char *bttn_names[32], uint8_t coords[32][2], const char *title) : Page(display, title)
{
    this->width = width;
    this->height = height;
    this->nrButtons = nrButtons;

    for(int i = 0; i < nrButtons; i++) {
        button[i].bttn = bttn_list[i];
        button[i].bttn_name = bttn_names[i];

        button[i].x = coords[i][0];
        button[i].y = coords[i][1];
    }
}

void PopUp::draw(const uint8_t *title_font, const uint8_t *content_font, bool title_is_centered)
{
    u8g2_SetFont(display, title_font);
    //displayPageTitle(title_is_centered);

    uint8_t x0 = (u8g2_GetDisplayWidth(display) - width) / 2, y0 = (u8g2_GetDisplayHeight(display) - height) / 2;
    uint8_t x1 = (u8g2_GetDisplayWidth(display) + width) / 2, y1 = (u8g2_GetDisplayHeight(display) + height) / 2;

    u8g2_SetFont(display, content_font);
    u8g2_SetClipWindow(display, x0, y0, x1, y1);
    u8g2_DrawFrame(display, x0, y0, width, height);
}

uint16_t PopUp::getHeight()
{
    return height;
}

uint16_t PopUp::getWidth()
{
    return width;
}