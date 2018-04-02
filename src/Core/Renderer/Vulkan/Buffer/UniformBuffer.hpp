//
// Created by MTesseracT on 2-4-2018.
//

#ifndef VULKANENGINEFIXED_UNIFORMBUFFER_HPP
#define VULKANENGINEFIXED_UNIFORMBUFFER_HPP

#include "Buffer.hpp"

namespace mt{
    //Interface for easier use in materials
    class UniformBuffer : Buffer
    {
    public:
        void update(vk::DeviceSize p_size, vk::DeviceSize p_offset, void* p_data);
    };
}


#endif //VULKANENGINEFIXED_UNIFORMBUFFER_HPP
