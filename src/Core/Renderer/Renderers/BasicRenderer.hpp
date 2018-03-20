//
// Created by MTesseracT on 15-3-2018.
//

#ifndef VULKANENGINEFIXED_BASICRENDERER_HPP
#define VULKANENGINEFIXED_BASICRENDERER_HPP


#include <Core/Renderer/Vulkan/Swapchain/Swapchain.hpp>
#include <Core/Renderer/Vulkan/RenderPass/RenderPass.hpp>

namespace mt{
    class BasicRenderer
    {
        Swapchain m_swapchain;
        RenderPass m_renderPass;

    public:
        void initialize();

        void destroy();

        void onResized();
    };
}



#endif //VULKANENGINEFIXED_BASICRENDERER_HPP
