//
// Created by MTesseracT on 12-3-2018.
//

#include <map>
#include "Device.hpp"

namespace mt
{
    void Device::create(vk::PhysicalDevice p_device)
    {

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

    vk::PhysicalDevice &Device::getPhysicalDevice()
    {
        return m_physicalDevice;
    }

    vk::Device &Device::getLogicalDevice()
    {
        return m_logicalDevice;
    }
}