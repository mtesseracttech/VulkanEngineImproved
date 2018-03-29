//
// Created by MTesseracT on 16-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include "RenderPass.hpp"

namespace mt
{

    void RenderPass::create(const Swapchain& p_swapchain)
    {
        const auto& device = Display::get().getDevice();

        m_depthStencil.create(p_swapchain.getExtent());

        vk::AttachmentDescription colorAttachment;
        colorAttachment.format         = p_swapchain.getImageFormat();
        colorAttachment.samples        = vk::SampleCountFlagBits::e1;
        colorAttachment.loadOp         = vk::AttachmentLoadOp::eClear;
        colorAttachment.storeOp        = vk::AttachmentStoreOp::eStore;
        colorAttachment.stencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
        colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        colorAttachment.initialLayout  = vk::ImageLayout::eUndefined;
        colorAttachment.finalLayout    = vk::ImageLayout::ePresentSrcKHR;

        vk::AttachmentDescription depthAttachment;
        depthAttachment.format         = m_depthStencil.getDepthFormat();
        depthAttachment.samples        = vk::SampleCountFlagBits::e1;
        depthAttachment.loadOp         = vk::AttachmentLoadOp::eClear;
        depthAttachment.storeOp        = vk::AttachmentStoreOp::eDontCare;
        depthAttachment.stencilLoadOp  = vk::AttachmentLoadOp::eDontCare;
        depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        depthAttachment.initialLayout  = vk::ImageLayout::eUndefined;
        depthAttachment.finalLayout    = vk::ImageLayout::eDepthStencilAttachmentOptimal;

        std::array<vk::AttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};

        vk::AttachmentReference colorAttachmentReference;
        colorAttachmentReference.attachment = 0;
        colorAttachmentReference.layout     = vk::ImageLayout::eColorAttachmentOptimal;

        vk::AttachmentReference depthAttachmentReference;
        depthAttachmentReference.attachment = 1;
        depthAttachmentReference.layout     = vk::ImageLayout::eDepthStencilAttachmentOptimal;

        vk::SubpassDescription subpassDescription;
        subpassDescription.pipelineBindPoint       = vk::PipelineBindPoint::eGraphics;
        subpassDescription.colorAttachmentCount    = 1;
        subpassDescription.pColorAttachments       = &colorAttachmentReference;
        subpassDescription.pDepthStencilAttachment = &depthAttachmentReference;

        vk::SubpassDependency subpassDependency;
        subpassDependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
        subpassDependency.dstSubpass    = 0;
        subpassDependency.srcStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        subpassDependency.srcAccessMask = vk::AccessFlagBits(0);
        subpassDependency.dstStageMask  = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        subpassDependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead |
                                          vk::AccessFlagBits::eColorAttachmentWrite;

        vk::RenderPassCreateInfo renderPassInfo;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments    = attachments.data();
        renderPassInfo.subpassCount    = 1;
        renderPassInfo.pSubpasses      = &subpassDescription;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies   = &subpassDependency;

        m_renderPass = device.createRenderPass(renderPassInfo);
    }

    const vk::RenderPass& RenderPass::getRenderPass() const
    {
        return m_renderPass;
    }

    void RenderPass::destroy()
    {
        const auto& device = Display::get().getDevice();

        if(m_renderPass) device.destroyRenderPass(m_renderPass);

        m_depthStencil.destroy();
    }
}