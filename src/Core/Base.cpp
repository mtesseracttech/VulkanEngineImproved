//
// Created by MTesseracT on 9-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Utility/Logger.hpp>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <iostream>
#include <Core/Input/MouseInput.hpp>
#include <Core/Input/KeyInput.hpp>
#include <Core/Maths/Time/GameTimer.hpp>
#include "Base.hpp"

namespace mt
{
    void Base::initialize()
    {
        Logger::log("Initializing Wolfsbane");
        Display::get().initialize();
        MouseInput::initialize();
        KeyInput::initialize();
        initializeTimers();
    }

    void Base::run()
    {
        setGameSpeed(30);

        auto& window = RenderWindow::get();

        double previous = GameTimer::current();
        double lag      = 0.0;

        while (!window.shouldWindowClose())
        {
            //Letting GLFW poll for events
            glfwPollEvents();

            //Calculating how many cycles the update needs to run
            double current = m_lagTimer.getElapsed();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;

            //Updating the input managers
            KeyInput::updateTimeNow(current);
            MouseInput::updateTimeNow(current);

            while (lag > m_timePerUpdate)
            {
                //Updating the deltatime first, so all objects in the same frame get the same DeltaTime
                GameTimer::update();

                //Removing however much time a game update tick takes
                lag -= m_timePerUpdate;
            }
        }
    }

    void Base::initializeTimers()
    {
        GameTimer::reset();
        m_lagTimer.reset();
    }

    void Base::setGameSpeed(int p_tps)
    {
        if (p_tps > 0)
        {
            m_ticksPerSecond = p_tps;
            m_timePerUpdate  = 1.0 / p_tps;
        }
    }

    void Base::cleanup()
    {
        Display::get().cleanup();
    }
}

