//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_SURFACEQUEUEFAMILIES_HPP
#define VULKANENGINEFIXED_SURFACEQUEUEFAMILIES_HPP

#include <vulkan/vulkan.hpp>

namespace mt
{
    class SurfaceQueueFamilies
    {
    private:
        int m_graphicsFamily = -1;
        int m_presentFamily  = -1;
    public:
        SurfaceQueueFamilies() = default;

        void create(vk::PhysicalDevice p_physicalDevice, vk::SurfaceKHR p_surface);

        bool isComplete();

        uint32_t getGraphicsFamily();

        uint32_t getPresentFamily();
    };
}


#endif //VULKANENGINEFIXED_SURFACEQUEUEFAMILIES_HPP
