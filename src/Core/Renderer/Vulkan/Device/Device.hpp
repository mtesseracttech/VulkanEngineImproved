//
// Created by MTesseracT on 12-3-2018.
//

#ifndef VULKANENGINEFIXED_DEVICE_HPP
#define VULKANENGINEFIXED_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.hpp>

namespace mt
{
    class Device
    {
    private:
        vk::PhysicalDevice m_physicalDevice;
        vk::Device         m_logicalDevice;

        SurfaceQueueFamilies m_queueFamilyIndices;

        struct{
            vk::Queue graphics;
            vk::Queue present;
        } m_queues;

        void createQueues();
    public:
        void create(vk::PhysicalDevice p_physicalDevice, std::vector<const char*> p_enabledExtensions);

        vk::PhysicalDevice& getPhysicalDevice();

        vk::Device& getLogicalDevice();

        static std::string getDeviceTypeName(vk::PhysicalDeviceType p_type);

        void destroy();
    };
}


#endif //VULKANENGINEFIXED_DEVICE_HPP
