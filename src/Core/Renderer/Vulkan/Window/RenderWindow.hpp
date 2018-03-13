//
// Created by MTesseracT on 8-3-2018.
//

#ifndef VULKANENGINEFIXED_RENDERWINDOW_HPP
#define VULKANENGINEFIXED_RENDERWINDOW_HPP

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>

namespace mt
{
    class RenderWindow
    {
        GLFWwindow *m_window = nullptr;
        vk::SurfaceKHR m_surface = nullptr;

        RenderWindow() = default;
    public:

        ~RenderWindow() = default;

        static RenderWindow& get();

        void create(glm::ivec2 p_windowSize, bool p_fullscreen, std::string p_windowTitle);

        void destroy();

        void createSurface();

        std::vector<const char*> getRequiredExtensions();

        bool shouldWindowClose();

        GLFWwindow * getGlfwWindowHandle();

        vk::SurfaceKHR& getSurface();

        void cleanupSurface();

        void close();
    };

}


#endif //VULKANENGINEFIXED_RENDERWINDOW_HPP