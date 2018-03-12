//
// Created by MTesseracT on 11-3-2018.
//

#ifndef VULKANENGINEFIXED_GAMETIMER_HPP
#define VULKANENGINEFIXED_GAMETIMER_HPP


#include <chrono>

namespace mt
{
    class GameTimer
    {
    public: //Typedefs
        typedef std::chrono::duration<double, std::ratio<1>> durationSec;
        typedef std::chrono::high_resolution_clock clock;
        typedef std::chrono::time_point<clock> timePoint;

    private:
        static timePoint m_current;
        static timePoint m_previous;
        static timePoint m_start;
        static double m_deltaTime;

        static void reset();
        static void update();

        friend class Base;

    public:
        static double delta();
        static double current();
        static double real();
    };
}



#endif //VULKANENGINEFIXED_GAMETIMER_HPP
