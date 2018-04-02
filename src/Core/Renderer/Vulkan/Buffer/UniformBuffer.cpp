//
// Created by MTesseracT on 2-4-2018.
//

#include "UniformBuffer.hpp"

namespace mt {
    void UniformBuffer::update(vk::DeviceSize p_size, vk::DeviceSize p_offset, void* p_data)
    {
        map(p_size, p_offset);
        copyTo(p_data, p_size);
        unmap();
    }
}