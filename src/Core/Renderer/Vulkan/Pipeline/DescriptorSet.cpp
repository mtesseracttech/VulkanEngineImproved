//
// Created by MTesseracT on 2-4-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "DescriptorSet.hpp"

namespace mt
{
    void DescriptorSet::create(const std::vector<DescriptorSetLayout>& p_layouts)
    {
        const auto& device = Display::get().getDevice();

        createDescriptorPool(device, p_layouts);

        allocateDescriptorSets(device, p_layouts);

        updateDescriptorSets(device);
    }

    void DescriptorSet::createDescriptorPool(const vk::Device& p_device, const std::vector<DescriptorSetLayout>& p_layouts)
    {
        std::map<vk::DescriptorType, uint32_t> descriptorCounts;

        for (const auto& layout : p_layouts)
        {
            for (const auto& descriptorSet : layout.getDescriptorCount())
            {
                descriptorCounts[descriptorSet.first] += descriptorSet.second;
            }
        }

        std::vector<vk::DescriptorPoolSize> poolSizes;
        for (const auto& descriptorSet : descriptorCounts)
        {
            vk::DescriptorPoolSize poolSize;
            poolSize.type = descriptorSet.first;
            poolSize.descriptorCount = descriptorSet.second;
        }

        vk::DescriptorPoolCreateInfo poolCreateInfo;
        poolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolCreateInfo.pPoolSizes = poolSizes.data();
        poolCreateInfo.maxSets = static_cast<uint32_t>(p_layouts.size());

        m_descriptorPool = p_device.createDescriptorPool(poolCreateInfo);
    }

    void DescriptorSet::allocateDescriptorSets(const vk::Device& p_device, const std::vector<DescriptorSetLayout>& p_layouts)
    {
        std::vector<vk::DescriptorSetLayout> layouts;
        for (const auto& layout : p_layouts)
        {
            layouts.push_back(layout.getLayout());
        }

        vk::DescriptorSetAllocateInfo allocateInfo;
        allocateInfo.descriptorPool = m_descriptorPool;
        allocateInfo.descriptorSetCount = static_cast<uint32_t>(p_layouts.size());
        allocateInfo.pSetLayouts = layouts.data();

        m_descriptorSets = p_device.allocateDescriptorSets(allocateInfo);
    }

    void DescriptorSet::updateDescriptorSets(const vk::Device& p_device)
    {

    }


}