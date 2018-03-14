//
// Created by MTesseracT on 8-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "RenderWindow.hpp"
#include <exception>
#include <iostream>
#include <Core/Utility/Logger.hpp>

namespace mt
{
    RenderWindow& RenderWindow::get()
    {
        static RenderWindow instance;
        return instance;
    }

    void RenderWindow::create(glm::ivec2 p_windowSize, bool p_fullscreen, std::string p_windowTitle)
    {
        if (glfwInit() != GLFW_TRUE) throw std::runtime_error("GLFW could not initialize properly");

        if (p_fullscreen)
        {
            const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            p_windowSize = {videoMode->width, videoMode->height};
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_window = glfwCreateWindow(p_windowSize.x, p_windowSize.y, p_windowTitle.c_str(),
                                    (p_fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

        if (m_window) Logger::log("Window was successfully created");
    }

    void RenderWindow::destroy()
    {
        destroySurface();
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void RenderWindow::createSurface()
    {
        Logger::log("Creating the window surface");
        auto instance = Display::get().getVulkanInstance();

        VkSurfaceKHR surface;

        if (glfwCreateWindowSurface(instance, m_window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create window surface");
        }

        m_surface = surface;
    }

    std::vector<const char*> RenderWindow::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        return extensions;
    }

    bool RenderWindow::shouldWindowClose()
    {
        return static_cast<bool>(glfwWindowShouldClose(m_window));
    }

    GLFWwindow* RenderWindow::getGlfwWindowHandle()
    {
        if (m_window == nullptr)
        {
            std::cout << m_window << std::endl;
        }
        return m_window;
    }

    vk::SurfaceKHR& RenderWindow::getSurface()
    {
        return m_surface;
    }

    void RenderWindow::close()
    {
        glfwWindowShouldClose(m_window);
    }

    void RenderWindow::destroySurface()
    {
        if (m_surface)
        {
            auto& instance = Display::get().getVulkanInstance();
            instance.destroySurfaceKHR(m_surface);
            m_surface = nullptr;
        }

    }


}

