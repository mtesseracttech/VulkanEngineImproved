//
// Created by mtesseract on 9-3-18.
//

#ifndef VULKANENGINEFIXED_MOUSEINPUT_HPP
#define VULKANENGINEFIXED_MOUSEINPUT_HPP

#include <map>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <Core/Maths/Time/Timer.hpp>

namespace mt
{
    enum MouseButton
    {
        Button1 = GLFW_MOUSE_BUTTON_1,
        Button2 = GLFW_MOUSE_BUTTON_2,
        Button3 = GLFW_MOUSE_BUTTON_3,
        Button4 = GLFW_MOUSE_BUTTON_4,
        Button5 = GLFW_MOUSE_BUTTON_5
    };

    class MouseInput
    {
        static bool                 m_prepared;
        static std::map<int, float> m_buttons;
        static Timer                m_timer;
        static double               m_timeNow;
        static double               m_timeStep;
        static glm::vec2            m_position;

        //GLFW callbacks
        static void mouseButtonCallback(GLFWwindow *p_window, int p_button, int p_action, int p_mods);

        static void mousePositionCallback(GLFWwindow *p_window, double p_xPos, double p_yPos);

        //Button Cache management functions
        static void buttonUp(int p_button);

        static void buttonDown(int p_button);

        //Technical functionality to be used by gamebase
        static void initialize();

        static void updateTimeNow(double p_timeNow);

        //Gamebase is supposed to initialize this manager
        friend class Base;

    public:
        //User Functionality

        /*
         * Returns true for a given mouse button approximately for 1 frame (60 fps taken as a base line)
         */
        static bool enter(MouseButton p_button);

        /*
         * Returns true as long as the given mouse button is pressed
         */
        static bool pressed(MouseButton p_button);

        /*
         * Gets the position of the mouse pointer
         */
        static glm::vec2 position();

    };
}


#endif //VULKANENGINEFIXED_MOUSEINPUT_HPP
