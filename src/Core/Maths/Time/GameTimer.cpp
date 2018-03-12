//
// Created by MTesseracT on 11-3-2018.
//

#include "GameTimer.hpp"


namespace mt
{
    GameTimer::timePoint GameTimer::m_current  = clock::now();
    GameTimer::timePoint GameTimer::m_previous = clock::now();
    GameTimer::timePoint GameTimer::m_start    = clock::now();

    double GameTimer::m_deltaTime = 0.0;

    void GameTimer::reset()
    {
        m_current   = clock::now();
        m_previous  = clock::now();
        m_start     = clock::now();
        m_deltaTime = 0.0;
    }

    void GameTimer::update()
    {
        m_previous  = m_current;
        m_current   = clock::now();
        m_deltaTime = std::chrono::duration_cast<durationSec>(m_current - m_previous).count();
    }

    double GameTimer::delta()
    {
        return m_deltaTime;
    }

    double GameTimer::current()
    {
        return std::chrono::duration_cast<durationSec>(m_current - m_start).count();
    }

    double GameTimer::real()
    {
        return std::chrono::duration_cast<durationSec>(clock::now() - m_start).count();
    }
}
