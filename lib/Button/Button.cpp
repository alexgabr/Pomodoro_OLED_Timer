#include "Button.h"

Button::Button()
{
    bttn_size.width = 0;
    bttn_size.height = 0;
    this->display = nullptr;
}

Button::Button(u8g2_t *display, uint8_t width, uint8_t height)
{
    bttn_size.width = width;
    bttn_size.height = height;
    this->display = display;
}

void Button::init(uint8_t x_text, uint8_t y_text, const char *text, bool is_inverted)
{
    // TODO: sa fac o functie prin care sa se poata seta nr de pixeli pentru auto-padding manual
    if(bttn_size.width < u8g2_GetStrWidth(display, text))
        bttn_size.width = u8g2_GetStrWidth(display, text) + 4; //two pixels for each side (or other multiple of 2)
    if(bttn_size.height < u8g2_GetAscent(display))
        bttn_size.height = u8g2_GetAscent(display) + 4; //same

    uint8_t x_frame = x_text - (bttn_size.width - u8g2_GetStrWidth(display, text)) / 2;
    uint8_t y_frame = y_text - (bttn_size.height + u8g2_GetAscent(display)) / 2;

    if(is_inverted){
        u8g2_SetDrawColor(display, 1);
        u8g2_DrawBox(display, x_frame, y_frame, bttn_size.width, bttn_size.height);

        u8g2_SetDrawColor(display, 0);
        u8g2_SetFontMode(display, 1);

        u8g2_DrawStr(display, x_text, y_text, text);
    }
    else{
        u8g2_SetDrawColor(display, 1);
        u8g2_DrawFrame(display, x_frame, y_frame, bttn_size.width, bttn_size.height);

        u8g2_DrawStr(display, x_text, y_text, text);        
    }
    
    //back to default
    u8g2_SetDrawColor(display, 1);
    u8g2_SetFontMode(display, 0);
}


void Button::setSize(uint8_t width, uint8_t height)
{
    bttn_size.width = width;
    bttn_size.height = height;
}

uint8_t Button::getWidth()
{
    return bttn_size.width;
}

uint8_t Button::getHeight()
{
    return bttn_size.height;
}