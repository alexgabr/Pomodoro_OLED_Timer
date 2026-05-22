#pragma once

#include "Arduino.h"
#include <U8g2lib.h>

#include "Gui.h"

void displayTimer(U8G2 &display, Gui &gui);
void displayStopWatch(U8G2 &display, Gui &gui);
void displaySettings(U8G2 &display, Gui &gui);