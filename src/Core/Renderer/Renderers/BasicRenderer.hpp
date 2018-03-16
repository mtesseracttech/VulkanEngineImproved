//
// Created by MTesseracT on 15-3-2018.
//

#ifndef VULKANENGINEFIXED_BASICRENDERER_HPP
#define VULKANENGINEFIXED_BASICRENDERER_HPP


#include <Core/Renderer/Vulkan/Swapchain/Swapchain.hpp>

namespace mt{
    class BasicRenderer
    {
        Swapchain m_swapchain;

    public:
        void initialize();
    };
}



#endif //VULKANENGINEFIXED_BASICRENDERER_HPP
