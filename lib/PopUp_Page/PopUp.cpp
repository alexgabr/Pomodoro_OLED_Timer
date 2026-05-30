#include "PopUp.h"

#include <bitmaps.h>

/* PRIVATE FUNCTIONS */
void PopUp::clearWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    u8g2_SetDrawColor(display, 0);
    for(uint8_t i = x0; i <= x1; i++)
        for(uint8_t j = y0; j <= x1; j++)
            u8g2_DrawPixel(display, i, j);

    u8g2_SetDrawColor(display, 1);
}

/* CONSTRUCTORS */
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

/* PUBLIC FUNCTIONS */
void PopUp::draw(const uint8_t *title_font, const uint8_t *content_font, bool title_is_centered)
{
    u8g2_SetDrawColor(display, 1);
    u8g2_SetBitmapMode(display, 1);
    for(uint8_t y = 0; y < u8g2_GetDisplayHeight(display); y += 8)
        for(uint8_t x = 0; x < u8g2_GetDisplayWidth(display); x += 8)
            u8g2_DrawXBM(display, x, y, 8, 8, background);

    uint8_t x0 = (u8g2_GetDisplayWidth(display) - width) / 2, y0 = (u8g2_GetDisplayHeight(display) - height) / 2;
    uint8_t x1 = (u8g2_GetDisplayWidth(display) + width) / 2, y1 = (u8g2_GetDisplayHeight(display) + height) / 2;

    u8g2_SetDrawColor(display, 1);
    u8g2_SetBitmapMode(display, 0);

    u8g2_SetClipWindow(display, x0, y0, x1, y1);
    
    clearWindow(x0, y0, x1, y1);
    u8g2_DrawFrame(display, x0, y0, width, height);

    u8g2_SetFont(display, title_font);
    displayPageTitle(width, height, true);

    u8g2_SetFont(display, content_font);
    for(uint8_t i = 0; i < nrButtons; i++)
        button[i].bttn.init(button[i].x, button[i].y, button[i].bttn_name);

    // end of function
    u8g2_SetMaxClipWindow(display);
}

uint16_t PopUp::getHeight()
{
    return height;
}

uint16_t PopUp::getWidth()
{
    return width;
}