//
// Created by MTesseracT on 21-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <exception>
#include "Pipeline.hpp"

namespace mt
{
    void Pipeline::create()
    {
        const auto& device = Display::get().getDevice();
        auto      & window = RenderWindow::get();

        vk::PipelineLayoutCreateInfo pipelineLayoutInfo;
        pipelineLayoutInfo.setLayoutCount = 1;
        //TODO: pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;

        m_pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);

        vk::PipelineVertexInputStateCreateInfo vertexInputInfo;
        //TODO: vertexInputInfo.vertexBindingDescriptionCount = 1;
        //TODO: vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        //TODO: vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        //TODO: vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        vk::PipelineInputAssemblyStateCreateInfo inputAssembly;
        inputAssembly.topology               = vk::PrimitiveTopology::eTriangleList;
        inputAssembly.primitiveRestartEnable = vk::Bool32(false);

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
        scissor.offset = {0, 0};
        scissor.extent = swapchainExtent;

        vk::PipelineViewportStateCreateInfo viewportState;
        viewportState.viewportCount = 1;
        viewportState.pViewports    = &viewport;
        viewportState.scissorCount  = 1;
        viewportState.pScissors     = &scissor;

        vk::PipelineRasterizationStateCreateInfo rasterizer;
        rasterizer.depthClampEnable        = vk::Bool32(false);
        rasterizer.rasterizerDiscardEnable = vk::Bool32(false);
        rasterizer.polygonMode             = vk::PolygonMode::eFill;
        rasterizer.lineWidth               = 1.0f;
        rasterizer.cullMode                = vk::CullModeFlagBits::eBack;
        rasterizer.frontFace               = vk::FrontFace::eCounterClockwise;
        rasterizer.depthBiasEnable         = vk::Bool32(false);

        vk::PipelineMultisampleStateCreateInfo multisampling = {};
        multisampling.sampleShadingEnable  = vk::Bool32(false);
        multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;

        vk::PipelineDepthStencilStateCreateInfo depthStencil;
        depthStencil.depthTestEnable       = vk::Bool32(true);
        depthStencil.depthWriteEnable      = vk::Bool32(true);
        depthStencil.depthCompareOp        = vk::CompareOp::eLess;
        depthStencil.depthBoundsTestEnable = vk::Bool32(false);
        depthStencil.stencilTestEnable     = vk::Bool32(false);

        vk::PipelineColorBlendAttachmentState colorBlendAttachment;
        colorBlendAttachment.colorWriteMask =
                vk::ColorComponentFlagBits::eR |
                vk::ColorComponentFlagBits::eG |
                vk::ColorComponentFlagBits::eB |
                vk::ColorComponentFlagBits::eA;
        colorBlendAttachment.blendEnable    = vk::Bool32(false);

        vk::PipelineColorBlendStateCreateInfo colorBlending;
        colorBlending.logicOpEnable = vk::Bool32(false);
        colorBlending.logicOp = vk::LogicOp::eCopy;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        vk::GraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.stageCount = static_cast<uint32_t>(m_stages.getShaderStages().size());
        pipelineInfo.pStages = m_stages.getShaderStages().data();
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = m_pipelineLayout;
        //TODO: pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = nullptr;

        //TODO: Pipelinecache addition
        m_pipeline = device.createGraphicsPipeline(nullptr, pipelineInfo);
    }

    void Pipeline::setShaderStages(ShaderStages p_stages)
    {
        m_stages = p_stages;
    }
}