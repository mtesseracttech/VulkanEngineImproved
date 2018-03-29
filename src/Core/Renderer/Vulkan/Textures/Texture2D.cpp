//
// Created by MTesseracT on 29-3-2018.
//

#include "Texture2D.hpp"

namespace mt
{
    void Texture2D::load(const std::string& p_filename, vk::ImageUsageFlags p_imageUsage, vk::ImageLayout p_layout,
                         bool p_linear)
    {
        auto& device = Display::get().getWrappedDevice();

        if (FileSystemHelpers::fileExists(p_filename))
        {
            std::stringstream error;
            error << "Could not find the following texture file: " << p_filename;
            throw std::runtime_error(error.str());
        }

        gli::texture2d texture(gli::load(p_filename));

        assert(!texture.empty());

        m_imageInfo.size      = vk::Extent2D(static_cast<uint32_t>(texture[0].extent().x),
                                             static_cast<uint32_t>(texture[0].extent().y));
        m_imageInfo.mipLevels = static_cast<uint32_t>(texture.levels());

        vk::Format           imageFormat       = getVulkanFormat(texture.format());
        vk::FormatProperties formatProperties  = device.getPhysicalDevice().getFormatProperties(imageFormat);
        vk::Bool32           useStaging        = vk::Bool32(!p_linear);
        vk::CommandBuffer    copyCommandBuffer = device.createCommandBuffer(vk::CommandBufferLevel::ePrimary, true);

        if (useStaging)
        {
            vk::DeviceMemory stagingMemory;

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
            stagingMemory = device.getLogicalDevice().allocateMemory(memoryAllocateInfo);
            device.getLogicalDevice().bindBufferMemory(stagingBuffer, stagingMemory, 0);

            uint8_t *data;
            device.getLogicalDevice().mapMemory(stagingMemory, 0, memoryRequirements.size, vk::MemoryMapFlagBits(0), static_cast<void**>(&data));
            memcpy(data, texture.data(), texture.size());
            device.getLogicalDevice().unmapMemory(stagingMemory);

            std::vector<vk::BufferImageCopy> bufferCopyRegions;
            uint32_t offset = 0;

            for (uint32_t i = 0; i < m_imageInfo.mipLevels; i++)
            {
                vk::BufferImageCopy bufferCopyRegion;
                bufferCopyRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
                bufferCopyRegion.imageSubresource.mipLevel = i;
                bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
                bufferCopyRegion.imageSubresource.layerCount = 1;
                bufferCopyRegion.imageExtent.width = static_cast<uint32_t>(texture[i].extent().x);
                bufferCopyRegion.imageExtent.height = static_cast<uint32_t>(texture[i].extent().y);
                bufferCopyRegion.imageExtent.depth = 1;
                bufferCopyRegion.bufferOffset = offset;

                bufferCopyRegions.push_back(bufferCopyRegion);

                offset += static_cast<uint32_t>(texture[i].size());
            }

            
        }
    }
}