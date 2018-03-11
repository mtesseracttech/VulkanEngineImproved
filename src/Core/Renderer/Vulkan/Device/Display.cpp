//
// Created by MTesseracT on 8-3-2018.
//

#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <iostream>
#include <Core/Utility/Logger.hpp>
#include "Display.hpp"

namespace mt
{
    Display &Display::get()
    {
        static Display instance;
        return instance;
    }

    void Display::initialize()
    {
        createWindow();
        createInstance();
        createDebug();
    }

    void Display::createWindow()
    {
        RenderWindow window = RenderWindow::get();
        window.create(glm::vec2(1280, 720), false, "Wolfsbane Engine");
        glfwSetWindowUserPointer(window.getGlfwWindowHandle(), this);
        //Todo: Adding the OnWindowResized Callback
    }

    void Display::createInstance()
    {
        if (m_debug.getEnableValidationLayers() && !m_debug.checkValidationLayerSupport())
        {
            throw std::runtime_error("Validation layers requested, but not available!");
        }

        auto extensions = getRequiredExtensions();

        vk::ApplicationInfo applicationInfo;
        applicationInfo.pApplicationName   = "Wolfsbane Engine";
        applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.pEngineName        = "Wolfsbane Engine";
        applicationInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        applicationInfo.apiVersion         = VK_API_VERSION_1_0;

        vk::InstanceCreateInfo createInfo;
        createInfo.pApplicationInfo        = &applicationInfo;
        createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();


        if (m_debug.getEnableValidationLayers())
        {
            createInfo.enabledLayerCount   = static_cast<uint32_t>(m_debug.getValidationLayers().size());
            createInfo.ppEnabledLayerNames = m_debug.getValidationLayers().data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        m_instance = vk::createInstance(createInfo, nullptr);
    }

    std::vector<const char *> Display::getRequiredExtensions()
    {
        std::vector<const char *> requiredExtensions = RenderWindow::get().getRequiredExtensions();

        if (m_debug.getEnableValidationLayers()) requiredExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

        return requiredExtensions;
    }

    void Display::createDebug()
    {

    }

    vk::Instance &Display::getVulkanInstance()
    {
        return m_instance;
    }


}


