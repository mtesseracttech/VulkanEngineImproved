//
// Created by MTesseracT on 21-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "DescriptorSetLayout.hpp"

namespace mt
{
    vk::DescriptorSetLayoutBinding DescriptorSetLayout::createLayoutBinding(uint32_t p_binding,
                                                                            vk::ShaderStageFlags p_shaderStage,
                                                                            vk::DescriptorType p_type)
    {
        ++m_descriptorCount[p_type];

        vk::DescriptorSetLayoutBinding layoutBinding;
        layoutBinding.binding            = p_binding;
        layoutBinding.descriptorCount    = 1;
        layoutBinding.descriptorType     = p_type;
        layoutBinding.pImmutableSamplers = nullptr;
        layoutBinding.stageFlags         = p_shaderStage;
        return layoutBinding;
    }

    const vk::DescriptorSetLayout DescriptorSetLayout::getLayout()const
    {
        return m_layout;
    }

    DescriptorSetLayout::DescriptorSetLayout(const std::vector<DescriptorSetComponent>& p_descriptorSets)
    {
        const auto& device = Display::get().getDevice();

        std::vector<vk::DescriptorSetLayoutBinding> layoutBindings;
        for (const auto& descriptorSet : p_descriptorSets)
        {
            layoutBindings.push_back(
                    createLayoutBinding(descriptorSet.m_binding, descriptorSet.m_shaderStage, descriptorSet.m_type));
        }

        vk::DescriptorSetLayoutCreateInfo layoutInfo;
        layoutInfo.bindingCount = static_cast<uint32_t>(layoutBindings.size());
        layoutInfo.pBindings    = layoutBindings.data();

        m_layout = device.createDescriptorSetLayout(layoutInfo);
    }

    const std::map<vk::DescriptorType, uint32_t>& DescriptorSetLayout::getDescriptorCount() const
    {
        return m_descriptorCount;
    }
}

