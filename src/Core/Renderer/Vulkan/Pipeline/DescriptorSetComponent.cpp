//
// Created by MTesseracT on 24-3-2018.
//

#include "DescriptorSetComponent.hpp"

namespace mt
{
    DescriptorSetComponent::DescriptorSetComponent(uint32_t p_binding, vk::DescriptorType p_type, vk::ShaderStageFlags p_shaderStage)
            : m_binding(p_binding),
              m_type(p_type),
              m_shaderStage(p_shaderStage)
    {}
}