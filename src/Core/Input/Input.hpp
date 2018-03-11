//
// Created by mtesseract on 9-3-18.
//

#ifndef VULKANENGINEFIXED_INPUT_HPP
#define VULKANENGINEFIXED_INPUT_HPP

#include "MouseInput.hpp"
#include "KeyInput.hpp"

namespace mt{
    class Input
    {
    private:
        MouseInput m_mouse;
        KeyInput m_keyboard;

        Input() = default;
        ~Input() = default;

        void initialize();
        void updateTimeNow(double p_timeNow);
        friend class Base;
    public:
        static Input & get();

        static bool getKey(KeyCode p_key);
        static bool getKeyDown(KeyCode p_key);
        static bool getMouseButton(MouseButton p_button);
        static bool getMouseButtonDown(MouseButton p_button);
        static glm::vec2 getMousePosition();
    };
}



#endif //VULKANENGINEFIXED_INPUT_HPP
