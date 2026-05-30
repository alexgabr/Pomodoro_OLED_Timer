#pragma once

#include <Arduino.h>

extern int pomodoro_time;

#define INACTIVITY 30000 // 30 seconds
#define BUTTON_DEBOUNCE 50 // ms

#define DEFAULT_POMODORO_TIME 25
#define DEFAULT_POPUP_WIDTH 90
#define DEFAULT_POPUP_HEIGHT 55


// PINS
const uint8_t selectButton = 16, upButton = 17, downButton = 18;
