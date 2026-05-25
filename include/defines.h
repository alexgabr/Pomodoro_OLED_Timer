#pragma once

#include <Arduino.h>

#define INACTIVITY 30000 // 30 seconds
#define BUTTON_DEBOUNCE 50 // ms
#define DEFAULT_POMODORO_TIME 5

// PINS
const uint8_t selectButton = 16, upButton = 17, downButton = 18;

extern int pomodoro_time;
