//
// Created by MTesseracT on 29-3-2018.
//

#include <Core/Renderer/Vulkan/Helpers/VulkanHelpers.hpp>
#include "Texture2D.hpp"

namespace mt
{
    void Texture2D::load(const std::string& p_filename, vk::ImageUsageFlags p_imageUsage, vk::ImageLayout p_layout)
    {
        auto      & device = Display::get().getWrappedDevice();
        const auto& queue  = device.getQueue(QueueType::GraphicsQueue);


        if (!FileSystemHelpers::fileExists(p_filename))
        {
            std::stringstream error;
            error << "Could not find the following texture file: " << p_filename;
            throw std::runtime_error(error.str());
            return;
        }

        gli::texture2d texture(gli::load(p_filename));

        assert(!texture.empty());

        m_imageInfo.size      = vk::Extent2D(static_cast<uint32_t>(texture[0].extent().x),
                                             static_cast<uint32_t>(texture[0].extent().y));
        m_imageInfo.mipLevels = static_cast<uint32_t>(texture.levels());

        vk::Format           imageFormat       = getVulkanFormat(texture.format());
        vk::FormatProperties formatProperties  = device.getPhysicalDevice().getFormatProperties(imageFormat);
        vk::CommandBuffer    copyCommandBuffer = device.createCommandBuffer(vk::CommandBufferLevel::ePrimary, true);

        vk::BufferCreateInfo bufferCreateInfo;
        bufferCreateInfo.size        = texture.size();
        bufferCreateInfo.usage       = vk::BufferUsageFlagBits::eTransferSrc;
        bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

        vk::Buffer             stagingBuffer      = device.getLogicalDevice().createBuffer(bufferCreateInfo);
        vk::MemoryRequirements memoryRequirements = device.getLogicalDevice().getBufferMemoryRequirements(
                stagingBuffer);

        vk::MemoryAllocateInfo memoryAllocateInfo;
        memoryAllocateInfo.allocationSize  = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = device.getMemoryType(memoryRequirements.memoryTypeBits,
                                                                  vk::MemoryPropertyFlagBits::eHostVisible |
                                                                  vk::MemoryPropertyFlagBits::eHostCoherent);

        vk::DeviceMemory stagingMemory          = device.getLogicalDevice().allocateMemory(memoryAllocateInfo);
        device.getLogicalDevice().bindBufferMemory(stagingBuffer, stagingMemory, 0);

        uint8_t* data;
        device.getLogicalDevice().mapMemory(stagingMemory, 0, memoryRequirements.size, vk::MemoryMapFlagBits(0),
                                            (void**)&data);
        memcpy(data, texture.data(), texture.size());
        device.getLogicalDevice().unmapMemory(stagingMemory);

        std::vector<vk::BufferImageCopy> bufferCopyRegions;
        uint32_t                         offset = 0;

        for (uint32_t i = 0; i < m_imageInfo.mipLevels; i++)
        {
            vk::BufferImageCopy bufferCopyRegion;
            bufferCopyRegion.imageSubresource.aspectMask     = vk::ImageAspectFlagBits::eColor;
            bufferCopyRegion.imageSubresource.mipLevel       = i;
            bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
            bufferCopyRegion.imageSubresource.layerCount     = 1;
            bufferCopyRegion.imageExtent.width               = static_cast<uint32_t>(texture[i].extent().x);
            bufferCopyRegion.imageExtent.height              = static_cast<uint32_t>(texture[i].extent().y);
            bufferCopyRegion.imageExtent.depth               = 1;
            bufferCopyRegion.bufferOffset                    = offset;

            bufferCopyRegions.push_back(bufferCopyRegion);

            offset += static_cast<uint32_t>(texture[i].size());
        }

        vk::ImageCreateInfo imageCreateInfo;
        imageCreateInfo.imageType     = vk::ImageType::e2D;
        imageCreateInfo.format        = imageFormat;
        imageCreateInfo.mipLevels     = m_imageInfo.mipLevels;
        imageCreateInfo.arrayLayers   = 1;
        imageCreateInfo.samples       = vk::SampleCountFlagBits::e1;
        imageCreateInfo.tiling        = vk::ImageTiling::eOptimal;
        imageCreateInfo.sharingMode   = vk::SharingMode::eExclusive;
        imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
        imageCreateInfo.extent        = vk::Extent3D(m_imageInfo.size.width, m_imageInfo.size.height, 1);
        imageCreateInfo.usage         = p_imageUsage;

        if (!(imageCreateInfo.usage & vk::ImageUsageFlagBits::eTransferDst))
            imageCreateInfo.usage |= vk::ImageUsageFlagBits::eTransferDst;

        m_image = device.getLogicalDevice().createImage(imageCreateInfo);

        memoryRequirements = device.getLogicalDevice().getImageMemoryRequirements(m_image);

        memoryAllocateInfo.allocationSize  = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = device.getMemoryType(memoryRequirements.memoryTypeBits,
                                                                  vk::MemoryPropertyFlagBits::eDeviceLocal);

        m_deviceMemory = device.getLogicalDevice().allocateMemory(memoryAllocateInfo);
        device.getLogicalDevice().bindImageMemory(m_image, m_deviceMemory, 0);

        vk::ImageSubresourceRange subresourceRange;
        subresourceRange.aspectMask   = vk::ImageAspectFlagBits::eColor;
        subresourceRange.baseMipLevel = 0;
        subresourceRange.levelCount   = m_imageInfo.mipLevels;
        subresourceRange.layerCount   = 1;

        VulkanHelpers::setImageLayout(copyCommandBuffer, m_image, vk::ImageLayout::eUndefined,
                                      vk::ImageLayout::eTransferDstOptimal, subresourceRange);
        copyCommandBuffer.copyBufferToImage(stagingBuffer, m_image, vk::ImageLayout::eTransferDstOptimal,
                                            static_cast<uint32_t>(bufferCopyRegions.size()), bufferCopyRegions.data());
        VulkanHelpers::setImageLayout(copyCommandBuffer, m_image, vk::ImageLayout::eTransferDstOptimal, p_layout,
                                      subresourceRange);

        m_imageLayout = p_layout;

        device.flushCommandBuffer(copyCommandBuffer, queue);
        device.getLogicalDevice().freeMemory(stagingMemory);
        device.getLogicalDevice().destroyBuffer(stagingBuffer);

        vk::SamplerCreateInfo samplerCreateInfo;
        samplerCreateInfo.magFilter     = vk::Filter::eLinear;
        samplerCreateInfo.minFilter     = vk::Filter::eLinear;
        samplerCreateInfo.mipmapMode    = vk::SamplerMipmapMode::eLinear;
        samplerCreateInfo.addressModeU  = vk::SamplerAddressMode::eRepeat;
        samplerCreateInfo.addressModeV  = vk::SamplerAddressMode::eRepeat;
        samplerCreateInfo.addressModeW  = vk::SamplerAddressMode::eRepeat;
        samplerCreateInfo.mipLodBias    = 0.0f;
        samplerCreateInfo.compareOp     = vk::CompareOp::eNever;
        samplerCreateInfo.minLod        = 0.0f;
        samplerCreateInfo.maxLod        = static_cast<float>(m_imageInfo.mipLevels);
        samplerCreateInfo.maxAnisotropy = device.getEnabledFeatures().samplerAnisotropy
                                          ? device.getProperties().limits.maxSamplerAnisotropy : 1.0f;
        samplerCreateInfo.anisotropyEnable = device.getEnabledFeatures().samplerAnisotropy;
        samplerCreateInfo.borderColor = vk::BorderColor::eFloatOpaqueWhite;

        m_sampler = device.getLogicalDevice().createSampler(samplerCreateInfo);

        vk::ImageViewCreateInfo viewCreateInfo;
        viewCreateInfo.viewType = vk::ImageViewType::e2D;
        viewCreateInfo.format = imageFormat;
        viewCreateInfo.components = vk::ComponentMapping(vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
        viewCreateInfo.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0,1,0,1);
        viewCreateInfo.subresourceRange.levelCount = m_imageInfo.mipLevels;
        viewCreateInfo.image = m_image;

        m_view = device.getLogicalDevice().createImageView(viewCreateInfo);

        updateDescriptor();
    }
}