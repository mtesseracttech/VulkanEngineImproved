//
// Created by mtesseract on 9-3-18.
//

#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include "MouseInput.hpp"

namespace mt
{
    void MouseInput::initialize()
    {
        if(m_prepared) return;

        auto window = RenderWindow::get().getGlfwWindowHandle();
        assert(window);
        glfwSetMouseButtonCallback(window, MouseInput::mouseButtonCallback);
        glfwSetCursorPosCallback(window, MouseInput::mousePositionCallback);

        m_timer.reset();

        m_prepared = true;
    }

    void MouseInput::mouseButtonCallback(GLFWwindow *p_window, int p_button, int p_action, int p_mods)
    {
        switch (p_action){
            case GLFW_PRESS:
                buttonDown(p_button);
                break;
            case GLFW_RELEASE:
                buttonUp(p_button);
                break;
            default:
                break;
        }
    }

    void MouseInput::mousePositionCallback(GLFWwindow *p_window, double p_xPos, double p_yPos)
    {
        m_position = glm::vec2(p_xPos, p_yPos);
    }

    void MouseInput::updateTimeNow(double p_timeNow)
    {
        m_timeNow = p_timeNow;
    }

    void MouseInput::buttonUp(int p_button)
    {
        m_buttons[p_button] = 0.0f;
    }

    void MouseInput::buttonDown(int p_button)
    {
        auto it = m_buttons.find(p_button);

        if (it != m_buttons.end() || m_buttons[p_button] == 0.0f)
        {
            m_buttons[p_button] = static_cast<float>(m_timer.getElapsed());
        }
    }

    glm::vec2 MouseInput::Position()
    {
        return m_position;
    }

    bool MouseInput::enter(MouseButton p_button)
    {
        auto it = m_buttons.find(p_button);

        if (it != m_buttons.end())
        {
            return m_buttons[p_button] > m_timeNow - m_timeStep;
        }
        return false;
    }

    bool MouseInput::pressed(MouseButton p_button)
    {
        auto it = m_buttons.find(p_button);

        if (it != m_buttons.end())
        {
            return m_buttons[p_button] > 0.0f;
        }
        return false;
    }
}
