//
// Created by MTesseracT on 24-3-2018.
//

#ifndef VULKANENGINEFIXED_DESCRIPTORSET_HPP
#define VULKANENGINEFIXED_DESCRIPTORSET_HPP


#include <vulkan/vulkan.hpp>

namespace mt
{
    struct DescriptorSet
    {
        DescriptorSet(uint32_t p_binding, vk::DescriptorType p_type, vk::ShaderStageFlags p_shaderStage);

        uint32_t             m_binding;
        vk::DescriptorType   m_type;
        vk::ShaderStageFlags m_shaderStage;
    };
}


#endif //VULKANENGINEFIXED_DESCRIPTORSET_HPP
