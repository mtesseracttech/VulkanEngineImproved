//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
#define VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP


#include <vulkan/vulkan.hpp>
#include <map>
#include "DescriptorSetComponent.hpp"

namespace mt
{
    class DescriptorSetLayout
    {
        std::map<vk::DescriptorType, uint32_t> m_descriptorCount;

        vk::DescriptorSetLayout m_layout = nullptr;

        vk::DescriptorSetLayoutBinding createLayoutBinding(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage,
                                                           vk::DescriptorType p_type);

    public:
        DescriptorSetLayout(const std::vector<DescriptorSetComponent>& p_descriptorSets);

        const vk::DescriptorSetLayout getLayout()const;

        const std::map<vk::DescriptorType, uint32_t>& getDescriptorCount() const;
    };
}


#endif //VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
