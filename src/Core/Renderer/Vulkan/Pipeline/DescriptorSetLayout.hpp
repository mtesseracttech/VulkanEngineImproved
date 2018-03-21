//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
#define VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP


#include <vulkan/vulkan.hpp>

namespace mt
{
    class DescriptorSetLayout
    {
        vk::DescriptorSetLayout                     m_layout = nullptr;
        std::vector<vk::DescriptorSetLayoutBinding> m_layoutBindings;

        void addDescriptorSet(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage, vk::DescriptorType p_type);


    public:
        void create();

        void addUniformBuffer(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage);

        void addCombinedImageSampler(uint32_t p_binding, vk::ShaderStageFlags p_shaderStage);

        const vk::DescriptorSetLayout getLayout();
    };
}


#endif //VULKANENGINEFIXED_DESCRIPTORSETLAYOUT_HPP
