//
// Created by mtesseract on 9-3-18.
//

#include "Input.hpp"

namespace mt{
    Input &Input::get()
    {
        static Input instance;
        return instance;
    }

    bool Input::getKey(KeyCode p_key)
    {
        return get().m_keyboard.enter(p_key);
    }

    bool Input::getKeyDown(KeyCode p_key)
    {
        return get().m_keyboard.pressed(p_key);
    }

    bool Input::getMouseButton(MouseButton p_button)
    {
        return get().m_mouse.enter(p_button);
    }

    bool Input::getMouseButtonDown(MouseButton p_button)
    {
        return get().m_mouse.pressed(p_button);
    }

    glm::vec2 Input::getMousePosition()
    {
        return get().m_mouse.Position();
    }

    void Input::initialize()
    {
        m_mouse.initialize();
        m_keyboard.initialize();
    }

    void Input::updateTimeNow(double p_timeNow)
    {
        m_mouse.updateTimeNow(p_timeNow);
        m_keyboard.updateTimeNow(p_timeNow);
    }


}

