//
// Created by MTesseracT on 20-3-2018.
//

#include <Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderProgram.hpp>
#include <Core/Renderer/Vulkan/Pipeline/PipelineCreateInfo.hpp>
#include <Core/Utility/Logger.hpp>
#include "PhongMaterial.hpp"

namespace mt
{
    PhongMaterial::PhongMaterial() : m_pipeline(PipelineCreateInfo(
            VertexLayout({ePosition, eNormal, eUV}),
            DescriptorSetLayout({DescriptorSetComponent(0,
                                                          vk::DescriptorType::eUniformBuffer,
                                                          vk::ShaderStageFlagBits::eVertex),
                                 DescriptorSetComponent(1,
                                                          vk::DescriptorType::eCombinedImageSampler,
                                                          vk::ShaderStageFlagBits::eFragment)}),
            ShaderProgram::loadShader("phong")))
    {}

    PhongMaterial::~PhongMaterial()
    {

    }

    void PhongMaterial::loadAssets(const std::string& p_assetName)
    {
        Logger::log("Loading phong assets for " + p_assetName);

        std::string assetPath = AssetLocations::TEXTURES + p_assetName + "/test_base.ktx";

        m_texture.load(assetPath, vk::ImageUsageFlagBits::eSampled, vk::ImageLayout::eShaderReadOnlyOptimal);
    }

    void PhongMaterial::initializePipeline(const RenderPass& p_renderPass)
    {
        m_pipeline.create(p_renderPass.getRenderPass());
    }

    PhongMaterial const* const PhongMaterial::load(const std::string& p_assetName)
    {
        return PhongMaterialLoader::m_cache.load(p_assetName);
    }

    void PhongMaterial::update(const glm::mat4& p_model, const glm::mat4& p_view, const glm::mat4& p_proj)
    {
        m_ubo.model = p_model;
        m_ubo.view = p_view;
        m_ubo.proj = p_proj;

        m_uniformBuffer.update(sizeof(m_ubo), 0, &m_ubo);
    }
}
