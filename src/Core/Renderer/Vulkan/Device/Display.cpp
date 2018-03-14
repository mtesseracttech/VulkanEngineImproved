//
// Created by MTesseracT on 8-3-2018.
//

#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <iostream>
#include <Core/Utility/Logger.hpp>
#include "Display.hpp"
#include "Device.hpp"
#include <sstream>
#include <map>
#include <Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.hpp>

namespace mt
{
    Display& Display::get()
    {
        static Display instance;
        return instance;
    }

    void Display::initialize()
    {
        createWindow();
        createInstance();
        createDebug();
        createSurface();
        createDevice();
    }

    void Display::createWindow()
    {
        Logger::log("Creating a Render Window");

        auto& window = RenderWindow::get();
        window.create(glm::vec2(1280, 720), false, "Wolfsbane Engine");
        glfwSetWindowUserPointer(window.getGlfwWindowHandle(), this);
        //Todo: Adding the OnWindowResized Callback
    }

    void Display::createInstance()
    {
        Logger::log("Creating a Vulkan Instance");

        if (VulkanDebug::m_enableValidationLayers && !m_debug.checkValidationLayerSupport())
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


        if (VulkanDebug::m_enableValidationLayers)
        {
            createInfo.enabledLayerCount   = static_cast<uint32_t>(VulkanDebug::m_validationLayers.size());
            createInfo.ppEnabledLayerNames = VulkanDebug::m_validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        m_instance = vk::createInstance(createInfo, nullptr);
    }

    std::vector<const char*> Display::getRequiredExtensions()
    {
        std::vector<const char*> requiredExtensions = RenderWindow::get().getRequiredExtensions();

        if (VulkanDebug::m_enableValidationLayers) requiredExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

        return requiredExtensions;
    }

    void Display::createDebug()
    {
        Logger::log("Creating Vulkan Debug callbacks");

        m_debug.create(m_instance);
    }


    void Display::createSurface()
    {
        Logger::log("Creating a surface for the window to display");

        RenderWindow::get().createSurface();
    }

    void Display::createDevice()
    {
        Logger::log("Selecting the best device for Wolfsbane to use");

        std::vector<vk::PhysicalDevice> devices = m_instance.enumeratePhysicalDevices();

        if (devices.empty()) throw std::runtime_error("No devices found with Vulkan support");
        else
        {
            Logger::log("Found the following Devices with Vulkan Support");
            int            devIndex = 0;
            for (const auto& device : devices)
            {
                vk::PhysicalDeviceProperties deviceProperties = device.getProperties();
                std::stringstream            line;
                line << "Device [" << devIndex << "] : " << deviceProperties.deviceName;
                Logger::log(line.str());
                line.str("");
                line << "Type: " << Device::getDeviceTypeName(deviceProperties.deviceType);
                Logger::log(line.str());
                line.str("");
                line << "API: " << (deviceProperties.apiVersion >> 22) << "."
                     << ((deviceProperties.apiVersion >> 12) & 0x3ff) << "." << (deviceProperties.apiVersion & 0xfff);
                Logger::log(line.str());
                ++devIndex;
            }
        }

        //Ranking the suitable devices
        std::multimap<int, vk::PhysicalDevice> scoredDevices;

        for (const auto& device : devices)
        {
            scoredDevices.insert(std::make_pair(getDeviceScore(device), device));
        }

        if (Logger::getLogLevel() <= LogLevel::Info)
        {
            int devIndex = 0;
            Logger::log("Scored the found devices as follows: ");
            for (const auto& device : scoredDevices)
            {
                vk::PhysicalDeviceProperties deviceProperties = device.second.getProperties();
                std::stringstream            line;
                line << "Device [" << devIndex << "] : " << deviceProperties.deviceName << " - Score: [" << device.first
                     << "]";
                Logger::log(line.str());
                ++devIndex;
            }
        }

        //Creating a logical device out of the best entry
        if (scoredDevices.rbegin()->first > 0) createLogicalDevice(scoredDevices.rbegin()->second);
        else throw std::runtime_error("No device with a score of over 0 was found");
    }

    int Display::getDeviceScore(vk::PhysicalDevice p_physicalDevice)
    {
        vk::PhysicalDeviceProperties properties = p_physicalDevice.getProperties();
        vk::PhysicalDeviceFeatures   features   = p_physicalDevice.getFeatures();

        int score = 0;

        SurfaceQueueFamilies queueFamilies;
        queueFamilies.create(p_physicalDevice, RenderWindow::get().getSurface());

        //If the queue families are not complete, using the device isn't going to happen
        if (!queueFamilies.isComplete()) return 0;

        //I'd like to play with tesselation and geometry shaders, so they would be required
        if (!features.tessellationShader || !features.geometryShader)
        {
            Logger::log("No tesselation or geometry shading capabilities, GPU not suitable");
            return 0;
        }

        // GPUS ranked based on desirability
        switch (properties.deviceType)
        {
            case vk::PhysicalDeviceType::eDiscreteGpu:
                score += 1000;
                break;
            case vk::PhysicalDeviceType::eIntegratedGpu:
                score += 800;
                break;
            case vk::PhysicalDeviceType::eCpu:
                score += 600;
                break;
            case vk::PhysicalDeviceType::eVirtualGpu:
                score += 400;
                break;
            case vk::PhysicalDeviceType::eOther:
                score += 200;
                break;
        }

        score += properties.limits.maxImageDimension2D;
        score += properties.limits.maxImageDimension3D;

        return score;
    }

    void Display::createLogicalDevice(vk::PhysicalDevice p_device)
    {
        Logger::log("Creating a logical device");

        std::vector<const char*> deviceExtensions {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        m_device.create(p_device, deviceExtensions);
    }

    vk::Instance& Display::getVulkanInstance()
    {
        return m_instance;
    }

    vk::PhysicalDevice& Display::getPhysicalDevice()
    {
        return m_device.getPhysicalDevice();
    }

    vk::Device& Display::getDevice()
    {
        return m_device.getLogicalDevice();
    }

    Device& Display::getWrappedDevice()
    {
        return m_device;
    }

    void Display::cleanup()
    {
        Logger::log("Wolfsbane is shutting down, cleaning up");
        destroyDevice();
        destroySurface();
        destroyDebug();
        destroyInstance();
        destroyWindow();
    }

    void Display::destroyDevice()
    {
        Logger::log("Destroying the Vulkan device");
        m_device.destroy();
    }

    void Display::destroySurface()
    {
        Logger::log("Destroying the Window Surface");
        RenderWindow::get().destroySurface();
    }

    void Display::destroyDebug()
    {
        Logger::log("Destroying the Vulkan Debug Callback");
        m_debug.destroy();
    }

    void Display::destroyInstance()
    {
        Logger::log("Destroying the Vulkan Instance");
        m_instance.destroy();
    }

    void Display::destroyWindow()
    {
        Logger::log("Destroying the Render Window");
        RenderWindow::get().destroy();
    }
}


