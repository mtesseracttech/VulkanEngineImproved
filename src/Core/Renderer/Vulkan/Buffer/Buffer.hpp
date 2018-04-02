//
// Created by MTesseracT on 2-4-2018.
//

#ifndef VULKANENGINEFIXED_BUFFER_HPP
#define VULKANENGINEFIXED_BUFFER_HPP

#include <vulkan/vulkan.hpp>

namespace mt
{
    class Buffer
    {
        vk::Buffer               m_buffer              = nullptr;
        vk::DeviceMemory         m_memory              = nullptr;
        vk::DescriptorBufferInfo m_descriptor          = nullptr;
        vk::DeviceSize           m_size                = vk::DeviceSize(0);
        vk::DeviceSize           m_alignment           = vk::DeviceSize(0);
        vk::BufferUsageFlags     m_usageFlags          = vk::BufferUsageFlagBits(0);
        vk::MemoryPropertyFlags  m_memoryPropertyFlags = vk::MemoryPropertyFlags(0);

        void* m_mapped = nullptr;

    protected:
        vk::Result map(vk::DeviceSize p_size = VK_WHOLE_SIZE, vk::DeviceSize p_offset = 0);

        void unmap();

        vk::Result bind(vk::DeviceSize p_offset = 0);

        void copyTo(void* p_data, vk::DeviceSize p_size);

        void setupDescriptor(vk::DeviceSize p_size = VK_WHOLE_SIZE, vk::DeviceSize p_offset = 0);

        vk::Result flush(vk::DeviceSize p_size = VK_WHOLE_SIZE, vk::DeviceSize p_offset = 0);

        vk::Result invalidate(vk::DeviceSize p_size = VK_WHOLE_SIZE, vk::DeviceSize p_offset = 0);

        void destroy();

    public:
        const vk::DescriptorBufferInfo& getDescriptor();
    };
}


#endif //VULKANENGINEFIXED_BUFFER_HPP
