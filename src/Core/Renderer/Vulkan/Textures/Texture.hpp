//
// Created by MTesseracT on 29-3-2018.
//

#ifndef VULKANENGINEFIXED_TEXTURE_HPP
#define VULKANENGINEFIXED_TEXTURE_HPP

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/IO/FileSystemHelpers.hpp>

#include <vulkan/vulkan.hpp>
#include <gli/gli.hpp>

#include <sstream>
#include <exception>

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
        }           m_imageInfo;

    protected:
        void updateDescriptor();

        vk::Format getVulkanFormat(gli::format p_format);

    public:
        void destroy();

        virtual void load(const std::string& p_filename,
                          vk::ImageUsageFlags p_imageUsage,
                          vk::ImageLayout p_layout,
                          bool p_linear) = 0;
    };
}


#endif //VULKANENGINEFIXED_TEXTURE_HPP
