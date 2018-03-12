//
// Created by MTesseracT on 12-3-2018.
//

#ifndef VULKANENGINEFIXED_DEVICE_HPP
#define VULKANENGINEFIXED_DEVICE_HPP

#include <vulkan/vulkan.hpp>

namespace mt
{
    class Device
    {
    private:
        vk::PhysicalDevice m_physicalDevice;
        vk::Device         m_logicalDevice;
    public:
        void create(vk::PhysicalDevice p_device);

        vk::PhysicalDevice& getPhysicalDevice();

        vk::Device& getLogicalDevice();

        static std::string getDeviceTypeName(vk::PhysicalDeviceType p_type);
    };
}


#endif //VULKANENGINEFIXED_DEVICE_HPP
