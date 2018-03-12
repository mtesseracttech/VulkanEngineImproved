//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_BASE_HPP
#define VULKANENGINEFIXED_BASE_HPP

#include "Maths/Time/Timer.hpp"

namespace mt
{
    class Base
    {
        Timer  m_lagTimer;
        int    m_ticksPerSecond;
        double m_timePerUpdate;

    public:
        void initialize();

        void run();

        void initializeTimers();

        void setGameSpeed(int p_tps);

        void cleanup();
    };
}


#endif //VULKANENGINEFIXED_BASE_HPP
