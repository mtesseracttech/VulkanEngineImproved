//
// Created by MTesseracT on 15-3-2018.
//

#include <Core/Renderer/Vulkan/Device/Display.hpp>
#include <Core/Renderer/Vulkan/Window/RenderWindow.hpp>
#include <Core/Utility/Logger.hpp>
#include <iostream>
#include "Swapchain.hpp"

namespace mt
{
    void Swapchain::create()
    {
        auto& physicalDevice = Display::get().getPhysicalDevice();
        auto& surface        = RenderWindow::get().getSurface();

        assert(physicalDevice && "Can't setup a Swapchain without a Device");
        assert(surface && "Can't setup a Swapchain without a Surface");

        m_queueFamilies.create(physicalDevice, surface);
    }

    void Swapchain::initialize()
    {
        auto& device  = Display::get().getWrappedDevice();
        auto& surface = RenderWindow::get().getSurface();

        assert(surface && "Can't initialize a Swapchain without a Surface");

        querySwapchainSupport(device.getPhysicalDevice(), surface);

        vk::SurfaceFormatKHR surfaceFormat = chooseSurfaceFormat();
        vk::PresentModeKHR   presentMode   = choosePresentMode();
        vk::Extent2D         extent        = chooseExtent();

        uint32_t imageCount = m_supportDetails.capabilities.minImageCount + 1;

        if (m_supportDetails.capabilities.maxImageCount > 0 && imageCount > m_supportDetails.capabilities.maxImageCount)
        {
            imageCount = m_supportDetails.capabilities.maxImageCount;
        }

        vk::SwapchainCreateInfoKHR createInfo;
        createInfo.surface          = surface;
        createInfo.minImageCount    = imageCount;
        createInfo.imageFormat      = surfaceFormat.format;
        createInfo.imageColorSpace  = surfaceFormat.colorSpace;
        createInfo.imageExtent      = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage       = vk::ImageUsageFlagBits::eColorAttachment;
        createInfo.presentMode      = presentMode;
        createInfo.preTransform     = m_supportDetails.capabilities.currentTransform;
        createInfo.compositeAlpha   = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        createInfo.clipped          = vk::Bool32(true);

        std::array<uint32_t, 2> indices = {m_queueFamilies.getGraphicsFamily(),
                                           m_queueFamilies.getPresentFamily()};

        if (m_queueFamilies.getGraphicsFamily() != m_queueFamilies.getPresentFamily())
        {
            createInfo.imageSharingMode      = vk::SharingMode::eConcurrent;
            createInfo.queueFamilyIndexCount = indices.size();
            createInfo.pQueueFamilyIndices   = indices.data();
        }
        else
        {
            createInfo.imageSharingMode = vk::SharingMode::eExclusive;
        }

        m_swapchain   = device.getLogicalDevice().createSwapchainKHR(createInfo);
        m_images      = device.getLogicalDevice().getSwapchainImagesKHR(m_swapchain);
        m_imageFormat = surfaceFormat.format;
        m_extent      = extent;

        createImageViews(device.getLogicalDevice());
    }

    void Swapchain::querySwapchainSupport(vk::PhysicalDevice p_physicalDevice, vk::SurfaceKHR p_surface)
    {
        m_supportDetails.capabilities = p_physicalDevice.getSurfaceCapabilitiesKHR(p_surface);
        m_supportDetails.formats      = p_physicalDevice.getSurfaceFormatsKHR(p_surface);
        m_supportDetails.presentModes = p_physicalDevice.getSurfacePresentModesKHR(p_surface);
    }

    vk::SurfaceFormatKHR Swapchain::chooseSurfaceFormat()
    {
        assert(!m_supportDetails.formats.empty());

        if (m_supportDetails.formats.size() == 1 && m_supportDetails.formats[0].format == vk::Format::eUndefined)
        {
            return {vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear};
        }

        for (const auto& availableFormat : m_supportDetails.formats)
        {
            if (availableFormat.format == vk::Format::eB8G8R8A8Unorm &&
                availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
            {
                return availableFormat;
            }
        }

        return m_supportDetails.formats[0];
    }

    vk::PresentModeKHR Swapchain::choosePresentMode()
    {
        assert(!m_supportDetails.presentModes.empty());

        vk::PresentModeKHR optimalPresentMode = vk::PresentModeKHR::eFifo;

        for (const auto& availablePresentMode : m_supportDetails.presentModes)
        {
            if (availablePresentMode == vk::PresentModeKHR::eMailbox)
            {
                return availablePresentMode;
            }
            else if (availablePresentMode == vk::PresentModeKHR::eImmediate)
            {
                optimalPresentMode = availablePresentMode;
            }
        }

        return optimalPresentMode;
    }

    vk::Extent2D Swapchain::chooseExtent()
    {
        if (m_supportDetails.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return m_supportDetails.capabilities.currentExtent;
        }
        else
        {
            auto& window = RenderWindow::get();
            glm::ivec2 windowSize = window.getSize();

            vk::Extent2D realExtent(static_cast<uint32_t >(windowSize.x), static_cast<uint32_t >(windowSize.y));

            vk::Extent2D minImageExtent = m_supportDetails.capabilities.minImageExtent;
            vk::Extent2D maxImageExtent = m_supportDetails.capabilities.maxImageExtent;

            realExtent.width  = std::max(minImageExtent.width, std::min(maxImageExtent.width, realExtent.width));
            realExtent.height = std::max(minImageExtent.height, std::min(maxImageExtent.height, realExtent.height));

            return realExtent;
        }
    }

    void Swapchain::createImageViews(vk::Device p_device)
    {
        m_imageViews.resize(m_images.size());

        for (uint32_t i = 0; i < m_images.size(); ++i)
        {
            m_imageViews[i] = createImageView(p_device, m_images[i], vk::ImageAspectFlagBits::eColor);
        }
    }

    vk::ImageView Swapchain::createImageView(vk::Device p_device, vk::Image p_image, vk::ImageAspectFlags p_aspectFlags)
    {
        vk::ImageViewCreateInfo createInfo;
        createInfo.image                           = p_image;
        createInfo.format                          = m_imageFormat;
        createInfo.viewType                        = vk::ImageViewType::e2D;
        createInfo.subresourceRange.aspectMask     = p_aspectFlags;
        createInfo.subresourceRange.baseMipLevel   = 0;
        createInfo.subresourceRange.levelCount     = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount     = 1;

        return p_device.createImageView(createInfo);
    }

    const vk::Extent2D Swapchain::getExtent() const
    {
        return m_extent;
    }

    const vk::Format Swapchain::getImageFormat() const
    {
        return m_imageFormat;
    }

    void Swapchain::destroy()
    {
        auto& device = Display::get().getDevice();

        for (auto& imageView : m_imageViews)
        {
            device.destroyImageView(imageView);
        }

        m_imageViews.clear();

        if (m_swapchain) device.destroySwapchainKHR(m_swapchain);

        m_swapchain = nullptr;
    }

}

