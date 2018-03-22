//
// Created by MTesseracT on 20-3-2018.
//

#include <Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderProgram.hpp>
#include "PhongMaterial.hpp"

namespace mt
{

    void PhongMaterial::create()
    {
    }

    void PhongMaterial::initialize(vk::RenderPass p_renderPass)
    {
        m_pipeline.create(p_renderPass);
    }

    PhongMaterial::PhongMaterial()
    {
        VertexLayout layout;
        layout.create({ePosition, eNormal, eUV});

        ShaderStages shader = ShaderProgram::loadShader("phong");

        DescriptorSetLayout descriptorSetLayout;
        descriptorSetLayout.addUniformBuffer(0, vk::ShaderStageFlagBits::eVertex);
        descriptorSetLayout.addCombinedImageSampler(1, vk::ShaderStageFlagBits::eFragment);

        m_pipeline.setup(layout, shader, descriptorSetLayout);
    }
}
