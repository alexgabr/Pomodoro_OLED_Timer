#pragma once

#include <Arduino.h>
#include <U8g2lib.h>


void content_changePomodoroDuration(uint8_t nr);
void content_alert(const char *message, uint8_t scroll, uint8_t &y);
void content_infoDevice(uint8_t scroll, uint8_t &y);