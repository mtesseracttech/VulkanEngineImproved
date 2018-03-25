//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
#define VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP


#include <vulkan/vulkan.hpp>
#include "DescriptorSet.hpp"

namespace mt
{
    class DescriptorSetLayout
    {
        vk::DescriptorSetLayout m_layout = nullptr;

        vk::DescriptorSetLayoutBinding createLayoutBinding(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage,
                                                           vk::DescriptorType p_type);

    public:
        DescriptorSetLayout(const std::vector<DescriptorSet>& p_descriptorSets);

        const vk::DescriptorSetLayout getLayout();


    };
}


#endif //VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
