//
// Created by MTesseracT on 21-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "DescriptorSetLayout.hpp"

namespace mt
{
    void DescriptorSetLayout::addDescriptorSet(uint32_t p_binding,
                                               vk::ShaderStageFlags p_shaderStage,
                                               vk::DescriptorType p_type)
    {
        vk::DescriptorSetLayoutBinding layoutBinding;
        layoutBinding.binding            = p_binding;
        layoutBinding.descriptorCount    = 1;
        layoutBinding.descriptorType     = p_type;
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBinding.stageFlags         = p_shaderStage;
        m_layoutBindings.push_back(layoutBinding);
    }

    void DescriptorSetLayout::addUniformBuffer(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage)
    {
        addDescriptorSet(p_binding, p_shaderStage, vk::DescriptorType::eUniformBuffer);
    }

    void DescriptorSetLayout::addCombinedImageSampler(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage)
    {
        addDescriptorSet(p_binding, p_shaderStage, vk::DescriptorType::eCombinedImageSampler);
    }

    void DescriptorSetLayout::create()
    {
        const auto& device = Display::get().getDevice();

        vk::DescriptorSetLayoutCreateInfo layoutInfo;
        layoutInfo.bindingCount = static_cast<uint32_t>(m_layoutBindings.size());
        layoutInfo.pBindings = m_layoutBindings.data();

        m_layout = device.createDescriptorSetLayout(layoutInfo);
    }

    const vk::DescriptorSetLayout DescriptorSetLayout::getLayout()
    {
        return m_layout;
    }


}

