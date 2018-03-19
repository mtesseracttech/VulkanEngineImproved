//
// Created by MTesseracT on 17-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "VulkanHelpers.hpp"

namespace mt
{

    uint32_t VulkanHelpers::findMemoryType(uint32_t p_typeFilter, vk::MemoryPropertyFlags p_properties)
    {
        const auto& device = Display::get().getPhysicalDevice();

        vk::PhysicalDeviceMemoryProperties memoryProperties = device.getMemoryProperties();

        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
        {
            if ((p_typeFilter & (1 << i)) &&
                (memoryProperties.memoryTypes[i].propertyFlags & p_properties) == p_properties)
                return i;
        }

        throw std::runtime_error("Failed to find a suitable memory type");
    }

    void VulkanHelpers::setImageLayout(vk::CommandBuffer p_commandbuffer,
                                       vk::Image p_image,
                                       vk::ImageLayout p_oldImageLayout,
                                       vk::ImageLayout p_newImageLayout,
                                       vk::ImageSubresourceRange p_subResourceRange,
                                       vk::PipelineStageFlags p_sourceStageMask,
                                       vk::PipelineStageFlags p_destinationStageMask)
    {
        // Create an image barrier object
        vk::ImageMemoryBarrier imageMemoryBarrier;
        imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        imageMemoryBarrier.oldLayout           = p_oldImageLayout;
        imageMemoryBarrier.newLayout           = p_newImageLayout;
        imageMemoryBarrier.image               = p_image;
        imageMemoryBarrier.subresourceRange    = p_subResourceRange;

        // Source layouts (old)
        // Source access mask controls actions that have to be finished on the old layout
        // before it will be transitioned to the new layout
        switch (p_oldImageLayout)
        {
            case vk::ImageLayout::eUndefined:
                // Image layout is undefined (or does not matter)
                // Only valid as initial layout
                // No flags required, listed only for completeness
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits(0);
                break;

            case vk::ImageLayout::ePreinitialized:
                // Image is preinitialized
                // Only valid as initial layout for linear images, preserves memory contents
                // Make sure host writes have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eHostWrite;
                break;

            case vk::ImageLayout::eColorAttachmentOptimal:
                // Image is a color attachment
                // Make sure any writes to the color buffer have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
                break;

            case vk::ImageLayout::eDepthStencilAttachmentOptimal:
                // Image is a depth/stencil attachment
                // Make sure any writes to the depth/stencil buffer have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
                break;

            case vk::ImageLayout::eTransferSrcOptimal:
                // Image is a transfer source
                // Make sure any reads from the image have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
                break;

            case vk::ImageLayout::eTransferDstOptimal:
                // Image is a transfer destination
                // Make sure any writes to the image have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
                break;

            case vk::ImageLayout::eShaderReadOnlyOptimal:
                // Image is read by a shader
                // Make sure any shader reads from the image have been finished
                imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eShaderRead;
                break;
            default:
                // Other source layouts aren't handled (yet)
                break;
        }

        // Target layouts (new)
        // Destination access mask controls the dependency for the new image layout
        switch (p_newImageLayout)
        {
            case vk::ImageLayout::eTransferDstOptimal:
                // Image will be used as a transfer destination
                // Make sure any writes to the image have been finished
                imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
                break;

            case vk::ImageLayout::eTransferSrcOptimal:
                // Image will be used as a transfer source
                // Make sure any reads from the image have been finished
                imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;
                break;

            case vk::ImageLayout::eColorAttachmentOptimal:
                // Image will be used as a color attachment
                // Make sure any writes to the color buffer have been finished
                imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
                break;

            case vk::ImageLayout::eDepthStencilAttachmentOptimal:
                // Image layout will be used as a depth/stencil attachment
                // Make sure any writes to depth/stencil buffer have been finished
                imageMemoryBarrier.dstAccessMask =
                        imageMemoryBarrier.dstAccessMask | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
                break;

            case vk::ImageLayout::eShaderReadOnlyOptimal:
                // Image will be read in a shader (sampler, input attachment)
                // Make sure any writes to the image have been finished
                if (imageMemoryBarrier.srcAccessMask == static_cast<vk::AccessFlagBits>(0))
                {
                    imageMemoryBarrier.srcAccessMask =
                            vk::AccessFlagBits::eHostWrite | vk::AccessFlagBits::eTransferWrite;
                }
                imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;
                break;
            default:
                // Other destination layouts aren't handled (yet)
                break;
        }

        // Put barrier inside setup command buffer
        p_commandbuffer.pipelineBarrier(p_sourceStageMask,
                                        p_destinationStageMask,
                                        static_cast<vk::DependencyFlagBits >(0),
                                        0, nullptr,
                                        0, nullptr,
                                        1, &imageMemoryBarrier);
    }

    void VulkanHelpers::setImageLayout(vk::CommandBuffer p_commandbuffer,
                                       vk::Image p_image,
                                       vk::ImageAspectFlags p_aspectMask,
                                       vk::ImageLayout p_oldImageLayout,
                                       vk::ImageLayout p_newImageLayout,
                                       vk::PipelineStageFlags p_sourceStageMask,
                                       vk::PipelineStageFlags p_destinationStageMask)
    {
        vk::ImageSubresourceRange subresourceRange;
        subresourceRange.aspectMask   = p_aspectMask;
        subresourceRange.baseMipLevel = 0;
        subresourceRange.levelCount   = 1;
        subresourceRange.layerCount   = 1;

        setImageLayout(p_commandbuffer, p_image, p_oldImageLayout, p_newImageLayout, subresourceRange,
                       p_sourceStageMask,
                       p_destinationStageMask);
    }
}