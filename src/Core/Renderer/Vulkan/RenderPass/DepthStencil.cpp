//
// Created by MTesseracT on 17-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Renderer/Vulkan/Swapchain/Swapchain.hpp>
#include <Core/Renderer/Vulkan/Helpers/VulkanHelpers.hpp>
#include "DepthStencil.hpp"

namespace mt
{
    void DepthStencil::create(vk::Extent2D p_swapchainExtent)
    {
        m_depthFormat = findDepthFormat();

        createDepthImage(p_swapchainExtent);

        m_depthImageView = createDepthImageView();

        auto& device = Display::get().getWrappedDevice();

        vk::CommandBuffer commandbuffer = device.createCommandBuffer(
                vk::CommandBufferLevel::ePrimary, true, GraphicsPool);

        VulkanHelpers::setImageLayout(commandbuffer, m_depthImage,
                                      vk::ImageAspectFlagBits::eDepth,
                                      vk::ImageLayout::eUndefined,
                                      vk::ImageLayout::eDepthStencilAttachmentOptimal);

        device.flushCommandBuffer(commandbuffer, device.getQueue(GraphicsQueue));

    }

    void DepthStencil::destroy()
    {
        const auto& device = Display::get().getDevice();

        if (m_depthImageView) device.destroyImageView(m_depthImageView);
        if (m_depthImage) device.destroyImage(m_depthImage);
        if (m_depthImageMemory) device.freeMemory(m_depthImageMemory);

        m_depthImageView   = nullptr;
        m_depthImage       = nullptr;
        m_depthImageMemory = nullptr;
        m_depthFormat      = vk::Format::eUndefined;
    }

    vk::Format DepthStencil::findDepthFormat()
    {
        const auto& physicalDevice             = Display::get().getPhysicalDevice();

        const std::vector<vk::Format> depthFormats{vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint,
                                                   vk::Format::eD24UnormS8Uint};
        const vk::FormatFeatureFlags  features = vk::FormatFeatureFlagBits::eDepthStencilAttachment;

        for (const auto& format : depthFormats)
        {
            vk::FormatProperties properties = physicalDevice.getFormatProperties(format);

            if ((properties.optimalTilingFeatures & features) == features) return format;
        }

        throw std::runtime_error("Could not find a suitable depth format!");
    }

    void DepthStencil::createDepthImage(vk::Extent2D p_extent)
    {
        const auto& device = Display::get().getDevice();

        vk::ImageCreateInfo imageInfo;
        imageInfo.imageType     = vk::ImageType::e2D;
        imageInfo.extent.width  = p_extent.width;
        imageInfo.extent.height = p_extent.height;
        imageInfo.extent.depth  = 1;
        imageInfo.mipLevels     = 1;
        imageInfo.arrayLayers   = 1;
        imageInfo.format        = m_depthFormat;
        imageInfo.tiling        = vk::ImageTiling::eOptimal;
        imageInfo.initialLayout = vk::ImageLayout::eUndefined;
        imageInfo.usage         = vk::ImageUsageFlagBits::eDepthStencilAttachment;
        imageInfo.samples       = vk::SampleCountFlagBits::e1;
        imageInfo.sharingMode   = vk::SharingMode::eExclusive;

        m_depthImage = device.createImage(imageInfo);

        vk::MemoryRequirements memoryRequirements = device.getImageMemoryRequirements(m_depthImage);

        vk::MemoryAllocateInfo memoryAllocateInfo;
        memoryAllocateInfo.allocationSize  = memoryRequirements.size;
        memoryAllocateInfo.memoryTypeIndex = VulkanHelpers::findMemoryType(memoryRequirements.memoryTypeBits,
                                                                           vk::MemoryPropertyFlagBits::eDeviceLocal);

        m_depthImageMemory = device.allocateMemory(memoryAllocateInfo);

        device.bindImageMemory(m_depthImage, m_depthImageMemory, 0);
    }

    vk::ImageView DepthStencil::createDepthImageView()
    {
        const auto& device = Display::get().getDevice();
        vk::ImageViewCreateInfo viewInfo;
        viewInfo.image                           = m_depthImage;
        viewInfo.viewType                        = vk::ImageViewType::e2D;
        viewInfo.format                          = m_depthFormat;
        viewInfo.subresourceRange.aspectMask     = vk::ImageAspectFlagBits::eDepth;
        viewInfo.subresourceRange.baseMipLevel   = 0;
        viewInfo.subresourceRange.levelCount     = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount     = 1;

        return device.createImageView(viewInfo);
    }

    const vk::Format& DepthStencil::getDepthFormat()
    {
        return m_depthFormat;
    }
}
