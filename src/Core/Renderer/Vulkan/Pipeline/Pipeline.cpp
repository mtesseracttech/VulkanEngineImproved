//
// Created by MTesseracT on 21-3-2018.
//

#include "Pipeline.hpp"
#include "PipelineCache.hpp"
#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <exception>

namespace mt
{
    void Pipeline::setup(VertexLayout p_vertexLayout, ShaderStages p_stages, DescriptorSetLayout p_descriptorSetLayout)
    {
        m_vertexLayout        = std::move(p_vertexLayout);
        m_stages              = std::move(p_stages);
        m_descriptorSetLayout = std::move(p_descriptorSetLayout);
    }

    void Pipeline::create(vk::RenderPass p_renderPass)
    {
        createPipelineLayout();
        createPipeline(p_renderPass);
    }

    void Pipeline::createPipeline(vk::RenderPass p_renderPass)
    {
        const auto& device = Display::get().getDevice();
        auto      & window = RenderWindow::get();
        const auto& cache  = PipelineCache::get().getPipelineCache();


        vk::PipelineVertexInputStateCreateInfo vertexInputState;
        vertexInputState.vertexBindingDescriptionCount   = m_vertexLayout.getBindingCount();
        vertexInputState.vertexAttributeDescriptionCount = m_vertexLayout.getAttributeCount();
        vertexInputState.pVertexBindingDescriptions      = m_vertexLayout.getBindings();
        vertexInputState.pVertexAttributeDescriptions    = m_vertexLayout.getAttributes();

        vk::PipelineInputAssemblyStateCreateInfo inputAssemblyState;
        inputAssemblyState.topology               = vk::PrimitiveTopology::eTriangleList;
        inputAssemblyState.primitiveRestartEnable = vk::Bool32(false);

        vk::Extent2D swapchainExtent(static_cast<uint32_t>(window.getSize().x),
                                     static_cast<uint32_t>(window.getSize().y));

        vk::Viewport viewport;
        viewport.x        = 0.0f;
        viewport.y        = 0.0f;
        viewport.width    = static_cast<float>(swapchainExtent.width);
        viewport.height   = static_cast<float>(swapchainExtent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        vk::Rect2D scissor;
        scissor.offset = vk::Offset2D(0, 0);
        scissor.extent = swapchainExtent;

        vk::PipelineViewportStateCreateInfo viewportState;
        viewportState.viewportCount = 1;
        viewportState.pViewports    = &viewport;
        viewportState.scissorCount  = 1;
        viewportState.pScissors     = &scissor;

        vk::PipelineRasterizationStateCreateInfo rasterizationState;
        rasterizationState.depthClampEnable        = vk::Bool32(false);
        rasterizationState.rasterizerDiscardEnable = vk::Bool32(false);
        rasterizationState.polygonMode             = vk::PolygonMode::eFill;
        rasterizationState.lineWidth               = 1.0f;
        rasterizationState.cullMode                = vk::CullModeFlagBits::eBack;
        rasterizationState.frontFace               = vk::FrontFace::eCounterClockwise;
        rasterizationState.depthBiasEnable         = vk::Bool32(false);

        vk::PipelineMultisampleStateCreateInfo multisamplingState = {};
        multisamplingState.sampleShadingEnable  = vk::Bool32(false);
        multisamplingState.rasterizationSamples = vk::SampleCountFlagBits::e1;

        vk::PipelineDepthStencilStateCreateInfo depthStencilState;
        depthStencilState.depthTestEnable       = vk::Bool32(true);
        depthStencilState.depthWriteEnable      = vk::Bool32(true);
        depthStencilState.depthCompareOp        = vk::CompareOp::eLess;
        depthStencilState.depthBoundsTestEnable = vk::Bool32(false);
        depthStencilState.stencilTestEnable     = vk::Bool32(false);

        vk::PipelineColorBlendAttachmentState colorBlendAttachment;
        colorBlendAttachment.colorWriteMask =
                vk::ColorComponentFlagBits::eR |
                vk::ColorComponentFlagBits::eG |
                vk::ColorComponentFlagBits::eB |
                vk::ColorComponentFlagBits::eA;
        colorBlendAttachment.blendEnable = vk::Bool32(false);

        vk::PipelineColorBlendStateCreateInfo colorBlendingState;
        colorBlendingState.logicOpEnable   = vk::Bool32(false);
        colorBlendingState.logicOp         = vk::LogicOp::eCopy;
        colorBlendingState.attachmentCount = 1;
        colorBlendingState.pAttachments    = &colorBlendAttachment;
        colorBlendingState.blendConstants[0] = 0.0f;
        colorBlendingState.blendConstants[1] = 0.0f;
        colorBlendingState.blendConstants[2] = 0.0f;
        colorBlendingState.blendConstants[3] = 0.0f;

        vk::GraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.stageCount          = static_cast<uint32_t>(m_stages.getShaderStages().size());
        pipelineInfo.pStages             = m_stages.getShaderStages().data();
        pipelineInfo.pVertexInputState   = &vertexInputState;
        pipelineInfo.pInputAssemblyState = &inputAssemblyState;
        pipelineInfo.pViewportState      = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizationState;
        pipelineInfo.pMultisampleState   = &multisamplingState;
        pipelineInfo.pDepthStencilState  = &depthStencilState;
        pipelineInfo.pColorBlendState    = &colorBlendingState;
        pipelineInfo.layout              = m_pipelineLayout;
        pipelineInfo.renderPass          = p_renderPass;
        pipelineInfo.subpass             = 0;
        pipelineInfo.basePipelineHandle  = nullptr;

        m_pipeline = device.createGraphicsPipeline(cache, pipelineInfo);
    }

    void Pipeline::createPipelineLayout()
    {
        const auto& device = Display::get().getDevice();

        vk::DescriptorSetLayout setLayout = m_descriptorSetLayout.getLayout();

        vk::PipelineLayoutCreateInfo pipelineLayoutInfo;
        pipelineLayoutInfo.setLayoutCount = 1;
        pipelineLayoutInfo.pSetLayouts    = &setLayout;

        m_pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);
    }
}