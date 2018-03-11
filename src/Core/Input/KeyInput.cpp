//
// Created by mtesseract on 9-3-18.
//

#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include "KeyInput.hpp"

namespace mt
{
    void KeyInput::initialize()
    {
        if (m_prepared) return;

        auto window = RenderWindow::get().getGlfwWindowHandle();
        assert(window);

        glfwSetKeyCallback(window, KeyInput::keyCallback);

        m_timer.reset();

        m_prepared = true;
    }

    void KeyInput::keyCallback(GLFWwindow *p_window, int p_key, int p_scancode, int p_action, int p_mod)
    {
        switch (p_action)
        {
            case GLFW_PRESS:
                keyDown(p_key);
                break;
            case GLFW_RELEASE:
                keyUp(p_key);
                break;
            default:
                break;
        }
    }

    void KeyInput::updateTimeNow(double p_timeNow)
    {
        m_timeNow = p_timeNow;
    }

    //Key State Management
    void KeyInput::keyUp(int p_key)
    {
        m_keys[p_key] = 0.0f;
    }

    void KeyInput::keyDown(int p_key)
    {
        auto it = m_keys.find(p_key);

        if (it != m_keys.end() || m_keys[p_key] == 0.0f)
        {
            m_keys[p_key] = static_cast<float>(m_timer.getElapsed());
        }
    }

    //Public Accessible Functions
    bool KeyInput::enter(KeyCode p_key)
    {
        auto it = m_keys.find(p_key);

        if (it != m_keys.end())
        {
            return m_keys[p_key] > m_timeNow - m_timeStep;
        }
        return false;
    }

    bool KeyInput::pressed(KeyCode p_key)
    {
        auto it = m_keys.find(p_key);

        if (it != m_keys.end())
        {
            return m_keys[p_key] > 0.0f;
        }
        return false;
    }
}