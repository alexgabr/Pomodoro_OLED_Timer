#include "content.h"

#include "defines.h"

#include <string.h>

extern U8G2 u8g2; // the display

void content_changePomodoroDuration(uint8_t nr) {
    uint8_t x_text = u8g2.getDisplayWidth() - DEFAULT_POPUP_WIDTH + 20;
    uint8_t y_text = (u8g2.getDisplayHeight() - DEFAULT_POPUP_HEIGHT) / 2 + 28;

    u8g2.setCursor(x_text, y_text);
    u8g2.print(u8x8_u8toa(nr, 2));

    y_text += 7;

    u8g2.setCursor(x_text, y_text);
    u8g2.print("min");
}

void content_alert(const char *message, uint8_t scroll) {
    uint8_t x_text = (128 - DEFAULT_POPUP_WIDTH) / 2 + 8; // beginning of the line
    uint8_t y_text = (64 - DEFAULT_POPUP_HEIGHT) / 2 + 20 - scroll; // first line
    uint8_t max_width = DEFAULT_POPUP_WIDTH - 16; // max width for each line

    char lineBuffer[64] = "";
    char wordBuffer[32];

    uint8_t msgI = 0, wordI = 0;

    while(true) {
        char c = message[msgI++];

        if(c != ' ' && c != '\0') {
            wordBuffer[wordI++] = c;
            wordBuffer[wordI] = '\0';
        }
        else {
            char testLine[100];

            strcpy(testLine, lineBuffer);
            if(strlen(testLine))
                strcat(testLine, " ");

            if(u8g2.getStrWidth(testLine) + u8g2.getStrWidth(wordBuffer) <= max_width) {
                strcat(testLine, wordBuffer);
                strcpy(lineBuffer, testLine);
            }
            else {
                u8g2.setCursor(x_text, y_text);
                u8g2.print(lineBuffer);

                y_text += 10;

                strcpy(lineBuffer, wordBuffer);
            }
            
            wordBuffer[0] = '\0';
            wordI = 0;
        }

        if(c == '\0') {
            u8g2.setCursor(x_text, y_text);
            u8g2.print(lineBuffer);
            break;
        }  
    }
}

void content_infoDevice(uint8_t scroll) {
    uint8_t x_text = (128 - DEFAULT_POPUP_WIDTH) / 2 + 8; // beginning of the line
    uint8_t y_text = (64 - DEFAULT_POPUP_HEIGHT) / 2 + 20 - scroll; // first line

    esp_chip_info_t info;
    esp_chip_info(&info);

    u8g2.setCursor(x_text, y_text);
    u8g2.print("Nr. of cores: ");
    u8g2.print(info.cores);

    y_text += 7;

    u8g2.setCursor(x_text, y_text);
    u8g2.print("Chip revision: ");
    u8g2.print(info.revision);
    
    y_text += 7;

    u8g2.setCursor(x_text, y_text);
    u8g2.print("Flash memory: ");
    u8g2.print(spi_flash_get_chip_size() / (1024 * 1024));
    u8g2.print(" MB");

    uint32_t upTime = millis() / 1000; // uptime in seconds
    uint16_t mins = upTime / 60, sec = upTime % 60;
    y_text += 7;

    u8g2.setCursor(x_text, y_text);
    u8g2.print("Uptime: ");

    if(mins > 99)
        u8g2.print(u8x8_u8toa(mins, 3));
    else
        u8g2.print(u8x8_u8toa(mins, 2));

    u8g2.print(':');
    u8g2.print(u8x8_u8toa(sec, 2));
}