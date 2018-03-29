//
// Created by MTesseracT on 29-3-2018.
//

#ifndef VULKANENGINEFIXED_TEXTURE_HPP
#define VULKANENGINEFIXED_TEXTURE_HPP

#include <vulkan/vulkan.hpp>

namespace mt
{
    class Texture
    {
    protected:
        vk::Image               m_image        = nullptr;
        vk::ImageView           m_view         = nullptr;
        vk::ImageLayout         m_imageLayout;
        vk::DeviceMemory        m_deviceMemory = nullptr;
        vk::DescriptorImageInfo m_desciptorImageInfo;

        vk::Sampler m_sampler;

        struct ImageInfo
        {
            vk::Extent2D size       = vk::Extent2D(0, 0);
            uint32_t     mipLevels  = 0;
            uint32_t     layerCount = 0;
        } m_imageInfo;

    protected:
        void updateDescriptor();

    public:
        void destroy();
    };
}


#endif //VULKANENGINEFIXED_TEXTURE_HPP
