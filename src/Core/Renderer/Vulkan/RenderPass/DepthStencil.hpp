//
// Created by MTesseracT on 17-3-2018.
//

#ifndef VULKANENGINEFIXED_DEPTHSTENCIL_HPP
#define VULKANENGINEFIXED_DEPTHSTENCIL_HPP


#include <vulkan/vulkan.hpp>

namespace mt
{
    class DepthStencil
    {
        vk::Format       m_depthFormat      = nullptr;
        vk::Image        m_depthImage       = nullptr;
        vk::DeviceMemory m_depthImageMemory = nullptr;
        vk::ImageView    m_depthImageView   = nullptr;

        vk::Format findDepthFormat();

        void createDepthImage(vk::Extent2D p_extent);

        vk::ImageView createDepthImageView();

    public:
        void create(vk::Extent2D p_swapchainExtent);
        void destroy();

        const vk::Format& getDepthFormat();
    };
}


#endif //VULKANENGINEFIXED_DEPTHSTENCIL_HPP
