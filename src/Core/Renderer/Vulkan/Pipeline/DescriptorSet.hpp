//
// Created by MTesseracT on 2-4-2018.
//

#ifndef VULKANENGINEFIXED_DESCRIPTORSET_HPP
#define VULKANENGINEFIXED_DESCRIPTORSET_HPP

#include "DescriptorSetLayout.hpp"

namespace mt{
    class DescriptorSet
    {
        vk::DescriptorPool m_descriptorPool = nullptr;

        std::vector<vk::DescriptorSet> m_descriptorSets;

    private:
        void createDescriptorPool(const vk::Device& p_device, const std::vector<DescriptorSetLayout>& p_layouts);
        void allocateDescriptorSets(const vk::Device& p_device, const std::vector<DescriptorSetLayout>& p_layouts);
        void updateDescriptorSets(const vk::Device& p_device);

    public:

        void create(const std::vector<DescriptorSetLayout>& p_layouts);
    };
}



#endif //VULKANENGINEFIXED_DESCRIPTORSET_HPP
