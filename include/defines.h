#pragma once

#include <Arduino.h>

extern uint8_t pomodoro_time;

#define INACTIVITY 30000 // 30 seconds
#define BUTTON_DEBOUNCE 50 // ms

#define DEFAULT_POMODORO_TIME 25
#define MIN_POMODORO_TIME 1

#define DEFAULT_POPUP_WIDTH 90
#define DEFAULT_POPUP_HEIGHT 55
#define DEFAULT_POPUP_TEXT_FONT u8g2_font_tiny5_t_all

#define DEFAULT_TITLE_FONT u8g2_font_profont12_mf
#define DEFAULT_TEXT_FONT u8g2_font_profont10_mf

// PINS
const uint8_t selectButton = 16, upButton = 17, downButton = 18;
