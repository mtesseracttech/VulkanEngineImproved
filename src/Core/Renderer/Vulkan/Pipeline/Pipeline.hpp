//
// Created by MTesseracT on 21-3-2018.
//

#ifndef VULKANENGINEFIXED_PIPELINE_HPP
#define VULKANENGINEFIXED_PIPELINE_HPP

#include <Core/Renderer/Vulkan/Assets/ShaderProgram/ShaderStages.hpp>
#include <Core/Renderer/Vulkan/Pipeline/VertexLayout.hpp>
#include "DescriptorSetLayout.hpp"
#include "PipelineCreateInfo.hpp"

namespace mt
{
    class Pipeline
    {
        vk::PipelineLayout m_pipelineLayout = nullptr;
        vk::Pipeline       m_pipeline       = nullptr;

        ShaderStages        m_stages;
        VertexLayout        m_vertexLayout;
        DescriptorSetLayout m_descriptorSetLayout;

    private:
        void createPipeline(vk::RenderPass p_renderPass);

        void createPipelineLayout();

    public:
        Pipeline(PipelineCreateInfo p_createInfo);

        void create(vk::RenderPass p_renderPass);
    };
}


#endif //VULKANENGINEFIXED_PIPELINE_HPP
