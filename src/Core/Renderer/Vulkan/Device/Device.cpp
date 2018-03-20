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

        createCommandPools();

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
        if (m_commandPools.graphics) m_logicalDevice.destroyCommandPool(m_commandPools.graphics);
        if (m_commandPools.present) m_logicalDevice.destroyCommandPool(m_commandPools.present);
        if (m_logicalDevice) m_logicalDevice.destroy();
    }

    vk::CommandBuffer
    Device::createCommandBuffer(vk::CommandBufferLevel p_level, bool p_begin, CommandPoolType p_poolType)
    {
        assert(m_logicalDevice);

        vk::CommandBufferAllocateInfo commandBufferAllocateInfo;
        commandBufferAllocateInfo.commandBufferCount = 1;
        commandBufferAllocateInfo.level              = p_level;

        switch (p_poolType)
        {
            case GraphicsPool :
                commandBufferAllocateInfo.commandPool = m_commandPools.graphics;
                break;
            case PresentPool:
                commandBufferAllocateInfo.commandPool = m_commandPools.present;
                break;
        }

        vk::CommandBuffer commandBuffer = m_logicalDevice.allocateCommandBuffers(commandBufferAllocateInfo)[0];

        if (p_begin)
        {
            vk::CommandBufferBeginInfo beginInfo;
            commandBuffer.begin(beginInfo);
        }

        return commandBuffer;

    }

    void Device::createCommandPools()
    {
        assert(m_logicalDevice && "Cannot create command pools without a logical device");
        vk::CommandPoolCreateInfo poolCreateInfo;
        poolCreateInfo.flags            = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
        poolCreateInfo.queueFamilyIndex = m_queueFamilyIndices.getGraphicsFamily();
        m_commandPools.graphics         = m_logicalDevice.createCommandPool(poolCreateInfo);

        poolCreateInfo.queueFamilyIndex = m_queueFamilyIndices.getPresentFamily();
        m_commandPools.present          = m_logicalDevice.createCommandPool(poolCreateInfo);
    }

    void Device::flushCommandBuffer(vk::CommandBuffer p_commandBuffer, vk::Queue p_queue, bool p_free)
    {
        if (!p_commandBuffer) return;

        p_commandBuffer.end();

        vk::FenceCreateInfo fenceCreateInfo;
        fenceCreateInfo.flags = vk::FenceCreateFlags(0);

        vk::Fence fence = m_logicalDevice.createFence(fenceCreateInfo);

        vk::SubmitInfo submitInfo;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers    = &p_commandBuffer;

        p_queue.submit(1, &submitInfo, fence);

        m_logicalDevice.waitForFences(1, &fence, vk::Bool32(true), 100000000000);

        m_logicalDevice.destroyFence(fence);

        if (p_free)
        {
            if (p_queue == m_queues.graphics)
            {
                m_logicalDevice.freeCommandBuffers(m_commandPools.graphics, 1, &p_commandBuffer);
            }
            else if (p_queue == m_queues.present)
            {
                m_logicalDevice.freeCommandBuffers(m_commandPools.present, 1, &p_commandBuffer);
            }
        }

    }

    vk::Queue Device::getQueue(QueueType p_type)
    {
        switch (p_type)
        {
            case GraphicsQueue:
                return m_queues.graphics;
            case PresentQueue:
                return m_queues.present;
        }
    }

    void Device::waitTillIdle()
    {
        m_logicalDevice.waitIdle();
    }
}