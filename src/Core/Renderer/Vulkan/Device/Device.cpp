//
// Created by MTesseracT on 12-3-2018.
//

#include <map>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <Core/Renderer/Vulkan/Debug/VulkanDebug.hpp>
#include <set>
#include <Core/Utility/Logger.hpp>
#include <iostream>
#include "Device.hpp"

namespace mt
{
    void Device::create(vk::PhysicalDevice p_physicalDevice, std::vector<const char*> p_enabledExtensions)
    {
        assert(p_physicalDevice && "No valid physical device was passed to the device wrapper");

        m_physicalDevice = p_physicalDevice;

        auto& surface                                              = RenderWindow::get().getSurface();
        assert(surface && "Surface was null, can't create any queues without it");

        m_queueFamilyIndices.create(m_physicalDevice, surface);

        std::vector<vk::DeviceQueueCreateInfo> queueCreateInfoList;
        std::set<uint32_t>                     uniqueQueueFamilies = {m_queueFamilyIndices.getGraphicsFamily(),
                                                                      m_queueFamilyIndices.getPresentFamily()};

        float queuePriority = 1.0f;

        for (auto queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount       = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfoList.push_back(queueCreateInfo);
        }

        vk::PhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.samplerAnisotropy = vk::Bool32(true);

        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.enabledExtensionCount   = static_cast<uint32_t>(p_enabledExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = p_enabledExtensions.data();
        deviceCreateInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfoList.size());
        deviceCreateInfo.pQueueCreateInfos       = queueCreateInfoList.data();
        deviceCreateInfo.pEnabledFeatures        = &deviceFeatures;

        if (VulkanDebug::m_enableValidationLayers)
        {
            deviceCreateInfo.enabledLayerCount   = static_cast<uint32_t>(VulkanDebug::m_validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = VulkanDebug::m_validationLayers.data();
        }
        else
        {
            deviceCreateInfo.enabledLayerCount = 0;
        }

        m_logicalDevice = m_physicalDevice.createDevice(deviceCreateInfo);

        createQueues();
    }

    std::string Device::getDeviceTypeName(vk::PhysicalDeviceType p_type)
    {
        const std::map<vk::PhysicalDeviceType, std::string> deviceNames{
                {vk::PhysicalDeviceType::eDiscreteGpu,   "Discrete"},
                {vk::PhysicalDeviceType::eIntegratedGpu, "Integrated"},
                {vk::PhysicalDeviceType::eCpu,           "CPU"},
                {vk::PhysicalDeviceType::eVirtualGpu,    "Virtual GPU"},
                {vk::PhysicalDeviceType::eOther,         "Other"}
        };
        return deviceNames.find(p_type)->second;
    }

    vk::PhysicalDevice& Device::getPhysicalDevice()
    {
        return m_physicalDevice;
    }

    vk::Device& Device::getLogicalDevice()
    {
        return m_logicalDevice;
    }

    void Device::createQueues()
    {
        Logger::log("Creating queues");
        m_queues.graphics = m_logicalDevice.getQueue(m_queueFamilyIndices.getGraphicsFamily(), 0);
        m_queues.present  = m_logicalDevice.getQueue(m_queueFamilyIndices.getPresentFamily(), 0);
    }

    void Device::destroy()
    {
        m_logicalDevice.destroy();
    }
}