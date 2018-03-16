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
        /*
         * A raw pointer to the GLFW window handle
         */
        GLFWwindow* m_window = nullptr;

        /*
         * Vulkan surface reference
         */
        vk::SurfaceKHR m_surface = nullptr;

        /*
         * Constructor
         */
        RenderWindow() = default;

    public:
        /*
         * Destructor
         */
        ~RenderWindow()
        {
            if (m_window != nullptr) destroy();
        };

        /*
         * Singleton instance
         */
        static RenderWindow& get();

        /*
         * Creates the GLFW window without any set API, this makes it possible for Vulkan to render in it.
         *
         * @param p_windowSize Allows you to specify the resolution of the renderwindow in pixels
         * @param p_fullscreen If set to true, will run GLFW in full screen
         * @param p_windowTitle Allows you to set a window title
         */
        void create(glm::ivec2 p_windowSize, bool p_fullscreen, std::string p_windowTitle);

        /*
         * Sets the GLFW window title
         *
         * @param p_windowTitle The window title that will be on top of the GLFW screen
         */
        void setTitle(std::string p_windowTitle);

        /*
         * Destroys the window object, will also destroy the surface if that has not been done yet
         */
        void destroy();

        /*
         * Creates the Vulkan Surface
         */
        void createSurface();

        /*
         * Returns all the extensions that GLFW will require to run with Vulkan support
         */
        std::vector<const char*> getRequiredExtensions();

        /*
         * Returns a raw GLFW window pointer, if required elsewhere in the application
         */
        GLFWwindow* getGlfwWindowHandle();

        /*
         * Returns the Vulkan Surface
         */
        vk::SurfaceKHR& getSurface();

        /*
         * When called, the window will make the "shouldWindowClose" return true
         */
        void close();

        /*
         * Returns true when GLFW has been flagged to close
         */
        bool shouldWindowClose();

        /*
         * Destroys the Vulkan Surface
         */
        void destroySurface();

        /*
         * Returns the window size as a GLM integer vec2
         */
        glm::ivec2 getSize();
    };

}


#endif //VULKANENGINEFIXED_RENDERWINDOW_HPP
