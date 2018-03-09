//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_DEVICEQUEUEINDICES_HPP
#define VULKANENGINEFIXED_DEVICEQUEUEINDICES_HPP


#include <vulkan/vulkan.hpp>
#include <vector>

namespace mt
{
    class DeviceQueueFamilies
    {
    private:
        std::vector<vk::QueueFamilyProperties> m_queueFamilyProperties;
    public:
        explicit DeviceQueueFamilies(vk::PhysicalDevice p_device);

        virtual ~DeviceQueueFamilies() = default;

        uint32_t getQueueFamilyIndex(vk::QueueFlags queueFlags);
    };
}


#endif //VULKANENGINEFIXED_DEVICEQUEUEINDICES_HPP
