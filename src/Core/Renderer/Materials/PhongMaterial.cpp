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
            DescriptorSetLayout({DescriptorSet(0,
                                               vk::DescriptorType::eUniformBuffer,
                                               vk::ShaderStageFlagBits::eVertex),
                                 DescriptorSet(1,
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
        
        std::string assetPath = AssetLocations::TEXTURES + p_assetName + "/diffuse.png";

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
}
