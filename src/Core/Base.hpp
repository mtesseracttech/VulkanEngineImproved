//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_BASE_HPP
#define VULKANENGINEFIXED_BASE_HPP

#include <Core/Renderer/Renderers/BasicRenderer.hpp>
#include "Maths/Time/Timer.hpp"

namespace mt
{
    class Base
    {
    private:
        Timer  m_lagTimer;
        int    m_ticksPerSecond  = 0;
        double m_timePerUpdate   = 0;
        int    m_framesPerSecond = 0;
        double m_timePerFrame    = 0;

        BasicRenderer m_renderer;

        void initializeRenderer();

        void initializeWindow();

        void initializeDisplay();

        void initializeInput();

        void initializeTimers();

        void setGameSpeed(int p_tps);

        void setRenderSpeed(int p_fps);

        void cleanupWindow();

        void cleanupDevice();

    public:
        void initialize();

        void run();

        void cleanup();

        void cleanupRenderer();
    };
}


#endif //VULKANENGINEFIXED_BASE_HPP
