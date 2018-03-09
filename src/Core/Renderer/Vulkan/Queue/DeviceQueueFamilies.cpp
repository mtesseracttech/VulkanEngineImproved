//
// Created by MTesseracT on 9-3-2018.
//

#include "DeviceQueueFamilies.hpp"

namespace mt
{
    uint32_t DeviceQueueFamilies::getQueueFamilyIndex(vk::QueueFlags queueFlags)
    {
        // Dedicated queue for compute
        // Try to find a queue family index that supports compute but not graphics
        if (queueFlags & vk::QueueFlagBits::eCompute)
        {
            for (uint32_t i = 0; i < static_cast<uint32_t>(m_queueFamilyProperties.size()); i++)
            {
                if ((m_queueFamilyProperties[i].queueFlags & queueFlags) &&
                    (static_cast<uint32_t>(m_queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) == 0))
                {
                    return i;
                }
            }
        }

        // Dedicated queue for transfer
        // Try to find a queue family index that supports transfer but not graphics and compute
        if (queueFlags & vk::QueueFlagBits::eTransfer)
        {
            for (uint32_t i = 0; i < static_cast<uint32_t>(m_queueFamilyProperties.size()); i++)
            {
                if ((m_queueFamilyProperties[i].queueFlags & queueFlags) &&
                    (static_cast<uint32_t>(m_queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) ==
                     0) &&
                    (static_cast<uint32_t>(m_queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eCompute ) == 0))
                {
                    return i;
                }
            }
        }

        // For other queue types or if no separate compute queue is present, return the first one to support the requested flags
        for (uint32_t i = 0; i < static_cast<uint32_t>(m_queueFamilyProperties.size()); i++)
        {
            if (m_queueFamilyProperties[i].queueFlags & queueFlags) return i;
        }

        throw std::runtime_error("Could not find a matching queue family index");
    }

    DeviceQueueFamilies::DeviceQueueFamilies(vk::PhysicalDevice p_device)
    {
        m_queueFamilyProperties = p_device.getQueueFamilyProperties();

        assert(!m_queueFamilyProperties.empty());
    }
}