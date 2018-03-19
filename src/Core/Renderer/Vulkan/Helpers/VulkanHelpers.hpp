//
// Created by MTesseracT on 17-3-2018.
//

#ifndef VULKANENGINEFIXED_VULKANHELPERS_HPP
#define VULKANENGINEFIXED_VULKANHELPERS_HPP


#include <vulkan/vulkan.hpp>

namespace mt
{
    class VulkanHelpers
    {
    public:
        static uint32_t findMemoryType(uint32_t p_typeFilter, vk::MemoryPropertyFlags p_properties);

        //Taken from https://github.com/SaschaWillems/Vulkan/blob/master/base/VulkanTools.cpp, only changed it to fit Vulkan.hpp style
        static void setImageLayout(vk::CommandBuffer p_commandbuffer,
                                   vk::Image p_image,
                                   vk::ImageLayout p_oldImageLayout,
                                   vk::ImageLayout p_newImageLayout,
                                   vk::ImageSubresourceRange p_subResourceRange,
                                   vk::PipelineStageFlags p_sourceStageMask = vk::PipelineStageFlagBits::eAllCommands,
                                   vk::PipelineStageFlags p_destinationStageMask = vk::PipelineStageFlagBits::eAllCommands);

        static void setImageLayout(vk::CommandBuffer p_commandbuffer,
                                   vk::Image p_image,
                                   vk::ImageAspectFlags p_aspectMask,
                                   vk::ImageLayout p_oldImageLayout,
                                   vk::ImageLayout p_newImageLayout,
                                   vk::PipelineStageFlags p_sourceStageMask = vk::PipelineStageFlagBits::eAllCommands,
                                   vk::PipelineStageFlags p_destinationStageMask = vk::PipelineStageFlagBits::eAllCommands);
    };

}


#endif //VULKANENGINEFIXED_VULKANHELPERS_HPP
