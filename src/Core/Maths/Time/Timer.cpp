//
// Created by mtesseract on 9-3-18.
//

#include "Timer.hpp"

Timer::Timer() : m_start(std::chrono::high_resolution_clock::now()) {}

void Timer::reset()
{
    m_start = chronoClock::now();
}

double Timer::getElapsed() const
{
    return std::chrono::duration_cast<chronoSecond>(chronoClock::now() - m_start).count();
}
