#include "Stopwatch.h"

void Stopwatch::start()
{
    if(!running) {
        running = true;
        startTime = millis() - elapsedTime;
    }
}

void Stopwatch::stop()
{
    if(running) {
        running = false;
        elapsedTime = millis() - startTime;
    }
}

void Stopwatch::restart()
{
    running = false;
    elapsedTime = 0;
}

uint32_t Stopwatch::getElapsedTime()
{
    if(running)
        return millis() - startTime;
    return elapsedTime;
}

void Stopwatch::getFormattedTime(uint16_t &minutes, uint8_t &seconds)
{
    uint32_t elapsed = getElapsedTime() / 1000; // convert milliseconds to seconds

    minutes = elapsed / 60;
    seconds = elapsed % 60;
}

bool Stopwatch::isRunning()
{
    return running;
}