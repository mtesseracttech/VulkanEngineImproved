//
// Created by MTesseracT on 2-4-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "Buffer.hpp"

namespace mt
{
    vk::Result Buffer::map(vk::DeviceSize p_size, vk::DeviceSize p_offset)
    {
        const auto& device = Display::get().getDevice();

        device.mapMemory(m_memory, p_offset, p_size, vk::MemoryMapFlags(0), &m_mapped);
    }

    void Buffer::unmap()
    {
        const auto& device = Display::get().getDevice();

        if (m_mapped)
        {
            device.unmapMemory(m_memory);
            m_mapped = nullptr;
        }
    }

    vk::Result Buffer::bind(vk::DeviceSize p_offset)
    {
        const auto& device = Display::get().getDevice();

        device.bindBufferMemory(m_buffer, m_memory, p_offset);
    }

    void Buffer::copyTo(void* p_data, vk::DeviceSize p_size)
    {
        assert(m_mapped);

        memcpy(m_mapped, p_data, p_size);
    }

    void Buffer::setupDescriptor(vk::DeviceSize p_size, vk::DeviceSize p_offset)
    {
        m_descriptor.offset = p_offset;
        m_descriptor.buffer = m_buffer;
        m_descriptor.range = p_size;
    }

    const vk::DescriptorBufferInfo& Buffer::getDescriptor()
    {
        return m_descriptor;
    }

    vk::Result Buffer::flush(vk::DeviceSize p_size, vk::DeviceSize p_offset)
    {
        const auto& device = Display::get().getDevice();

        vk::MappedMemoryRange mappedMemoryRange;
        mappedMemoryRange.memory = m_memory;
        mappedMemoryRange.offset = p_offset;
        mappedMemoryRange.size = p_size;

        return device.flushMappedMemoryRanges(1, &mappedMemoryRange);
    }

    vk::Result Buffer::invalidate(vk::DeviceSize p_size, vk::DeviceSize p_offset)
    {
        const auto& device = Display::get().getDevice();

        vk::MappedMemoryRange mappedMemoryRange;
        mappedMemoryRange.memory = m_memory;
        mappedMemoryRange.offset = p_offset;
        mappedMemoryRange.size = p_size;

        return device.invalidateMappedMemoryRanges(1, &mappedMemoryRange);
    }

    void Buffer::destroy()
    {
        const auto& device = Display::get().getDevice();

        if(m_buffer) device.destroyBuffer(m_buffer);
        if(m_memory) device.freeMemory(m_memory);

        m_buffer = nullptr;
        m_memory = nullptr;
    }
}