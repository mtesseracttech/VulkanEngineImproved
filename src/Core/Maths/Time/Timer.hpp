//
// Created by mtesseract on 9-3-18.
//

#ifndef VULKANENGINEFIXED_TIMER_HPP
#define VULKANENGINEFIXED_TIMER_HPP


#include <iostream>
#include <chrono>
#include <cstdlib>

class Timer
{
private:
    typedef std::chrono::high_resolution_clock chronoClock;
    typedef std::chrono::duration<double, std::ratio<1> > chronoSecond;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    
public:
    Timer();

    void reset();

    double getElapsed() const;
};


#endif //VULKANENGINEFIXED_TIMER_HPP
