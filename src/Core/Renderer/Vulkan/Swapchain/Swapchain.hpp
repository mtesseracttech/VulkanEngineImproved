//
// Created by MTesseracT on 15-3-2018.
//

#ifndef VULKANENGINEFIXED_SWAPCHAIN_HPP
#define VULKANENGINEFIXED_SWAPCHAIN_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Queue/SurfaceQueueFamilies.hpp>

namespace mt
{
    class Swapchain
    {
    private:
        vk::SwapchainKHR           m_swapchain = nullptr;

        std::vector<vk::Image>     m_images;
        std::vector<vk::ImageView> m_imageViews;

        vk::Format                 m_imageFormat;
        vk::Extent2D               m_extent;

        SurfaceQueueFamilies m_queueFamilies;

        struct
        {
            vk::SurfaceCapabilitiesKHR        capabilities;
            std::vector<vk::SurfaceFormatKHR> formats;
            std::vector<vk::PresentModeKHR>   presentModes;
        } m_supportDetails;

    private:
        void querySwapchainSupport(vk::PhysicalDevice p_physicalDevice, vk::SurfaceKHR p_surface);

        vk::SurfaceFormatKHR chooseSurfaceFormat();

        vk::PresentModeKHR choosePresentMode();

        vk::Extent2D chooseExtent();

        void createImageViews(vk::Device p_device);

        vk::ImageView createImageView(vk::Device p_device, vk::Image p_image, vk::ImageAspectFlags p_aspectFlags);

    public:
        void create();

        void initialize();

        void destroy();

        const vk::Extent2D getExtent() const;

        const vk::Format getImageFormat() const;
    };

}


#endif //VULKANENGINEFIXED_SWAPCHAIN_HPP
