//
// Created by MTesseracT on 9-3-2018.
//

#include <iostream>
#include "SurfaceQueueFamilies.hpp"

namespace mt
{
    bool SurfaceQueueFamilies::isComplete()
    {
        return m_graphicsFamily >= 0 && m_presentFamily >= 0;
    }

    uint32_t SurfaceQueueFamilies::getGraphicsFamily()
    {
        return static_cast<uint32_t>(m_graphicsFamily);
    }

    uint32_t SurfaceQueueFamilies::getPresentFamily()
    {
        return static_cast<uint32_t>(m_presentFamily);
    }

    void SurfaceQueueFamilies::create(vk::PhysicalDevice p_physicalDevice, vk::SurfaceKHR p_surface)
    {
        std::vector<vk::QueueFamilyProperties> queueFamilies = p_physicalDevice.getQueueFamilyProperties();

        int i = 0;

        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                m_graphicsFamily = i;
            }

            auto presentSupport = p_physicalDevice.getSurfaceSupportKHR(i, p_surface);

            if (queueFamily.queueCount > 0 && presentSupport)
            {
                m_presentFamily = i;
            }

            if (isComplete()) break;

            ++i;
        }
    }
}

