//
// Created by MTesseracT on 16-3-2018.
//

#ifndef VULKANENGINEFIXED_RENDERPASS_HPP
#define VULKANENGINEFIXED_RENDERPASS_HPP

#include <vulkan/vulkan.hpp>

namespace mt
{
    class RenderPass
    {
        vk::RenderPass m_renderPass;

        void create();
    };
}



#endif //VULKANENGINEFIXED_RENDERPASS_HPP
