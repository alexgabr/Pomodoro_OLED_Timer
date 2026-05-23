#pragma once

#include <Arduino.h>

class Timer {
    private:
        uint32_t startTime;
        uint32_t elapsedTime = 0;
        uint32_t duration;

        bool running = false;
    public:
        Timer(uint32_t duration);
        void start();
        void stop();
        void reset();

        uint32_t getElapsedTime();
        uint32_t getRemainingTime();
        bool isRunning();

        void getFormattedTime(uint8_t &minutes, uint8_t &seconds);

};