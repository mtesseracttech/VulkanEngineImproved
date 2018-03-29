//
// Created by MTesseracT on 12-3-2018.
//

#ifndef VULKANENGINEFIXED_DEVICE_HPP
#define VULKANENGINEFIXED_DEVICE_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.hpp>

namespace mt
{
    enum QueueType{
        GraphicsQueue,
        PresentQueue
    };

    enum CommandPoolType{
        GraphicsPool,
        PresentPool
    };

    class Device
    {
    private:
        /*
         * The physical device represents the piece of hardware the device wrapper is made out of
         */
        vk::PhysicalDevice m_physicalDevice = nullptr;
        /*
         * The logical device represents a logical connection to a physical device, it is used to call most of vulkans functionality from
         */
        vk::Device         m_logicalDevice  = nullptr;

        /*
         * Stores the memory properties containing the available types of memory from the physical device
         */
        vk::PhysicalDeviceMemoryProperties m_memoryProperties;

        /*
         * Wrapper object to search for and contain queue family indices relating to the surface
         */
        SurfaceQueueFamilies m_queueFamilyIndices;

        /*
         * The command pools that command buffer memory is allocated from
         */
        struct
        {
            vk::CommandPool graphics = nullptr;
            vk::CommandPool present  = nullptr;
        } m_commandPools;

        /*
         * Contains the command queues that commands can be commited to
         */
        struct
        {
            vk::Queue graphics = nullptr;
            vk::Queue present  = nullptr;
        } m_queues;

    private:

        void createQueues();

        void createCommandPools();

    public:
        static std::string getDeviceTypeName(vk::PhysicalDeviceType p_type);

        void create(vk::PhysicalDevice p_physicalDevice, std::vector<const char*> p_enabledExtensions);

        void destroy();


        /*
         * Gets a reference to the used vulkan physical device
         */
        vk::PhysicalDevice& getPhysicalDevice();

        /*
         * Gets a reference to the used vulkan logical device
         */
        vk::Device& getLogicalDevice();

        /*
         * Creates a command buffer from the selected type and begins it
         */
        vk::CommandBuffer createCommandBuffer(vk::CommandBufferLevel p_level, bool p_begin = false, CommandPoolType p_poolType = GraphicsPool);

        void flushCommandBuffer(vk::CommandBuffer p_commandBuffer, vk::Queue p_queue, bool p_free = true);

        vk::Queue getQueue(QueueType p_type);

        void waitTillIdle();

        uint32_t getMemoryType(uint32_t p_typeBits, vk::MemoryPropertyFlags p_properties, vk::Bool32* p_found = nullptr);
    };
}


#endif //VULKANENGINEFIXED_DEVICE_HPP
