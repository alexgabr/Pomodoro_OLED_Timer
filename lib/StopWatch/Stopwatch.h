#pragma once

#include <Arduino.h>

class Stopwatch
{
    private:
        uint32_t startTime;
        uint32_t elapsedTime = 0;
        uint32_t pausedTime = 0;

        bool running = false;
    public:
        void start();
        void stop();
        void restart();

        bool isRunning();

        uint32_t getElapsedTime();
        void getFormattedTime(uint16_t &minutes, uint8_t &seconds);
};