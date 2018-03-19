//
// Created by MTesseracT on 16-3-2018.
//

#ifndef VULKANENGINEFIXED_RENDERPASS_HPP
#define VULKANENGINEFIXED_RENDERPASS_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Swapchain/Swapchain.hpp>
#include "DepthStencil.hpp"

namespace mt
{
    class RenderPass
    {
        vk::RenderPass m_renderPass = nullptr;

        DepthStencil m_depthStencil;

    public:
        void create(Swapchain p_swapchain);
        void destroy();

        vk::RenderPass& getRenderPass();
    };
}


#endif //VULKANENGINEFIXED_RENDERPASS_HPP
