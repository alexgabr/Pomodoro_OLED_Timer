#include "Timerlib.h"

Timer::Timer(uint32_t duration) {
    this->duration = duration;
}

void Timer::start() 
{
    if(!running) {
        running = true;
        startTime = millis() - elapsedTime;
    }
}

void Timer::stop()
{
    if(running) {
        elapsedTime = millis() - startTime;
        running = false;
    }
}

void Timer::reset()
{
    running = false;
    elapsedTime = 0;
}

uint32_t Timer::getElapsedTime()
{
    if(running)
        return millis() - startTime;
    return elapsedTime;
}

uint32_t Timer::getRemainingTime()
{
    uint32_t elapsed = getElapsedTime();
    if(elapsed > duration) {
        reset();
        return 0;
    }

    return duration - elapsed;
}

void Timer::getFormattedTime(uint8_t &minutes, uint8_t &seconds)
{
    uint32_t remainingSec = getRemainingTime() / 1000;

    minutes = remainingSec / 60;
    seconds = remainingSec % 60;
}