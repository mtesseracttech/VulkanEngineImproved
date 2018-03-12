//
// Created by MTesseracT on 8-3-2018.
//

#ifndef VULKANENGINEFIXED_DISPLAY_HPP
#define VULKANENGINEFIXED_DISPLAY_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Debug/VulkanDebug.hpp>
#include "Device.hpp"

namespace mt
{
    class Display
    {
    private:
        /*
         * The vulkan instance handle.
         * Used for creation of the Physical Device
         */
        vk::Instance m_instance = nullptr;

        /*
         * Reference to the VulkanDebug class.
         * Contains functions to let Vulkan give us debug reports.
         */
        VulkanDebug m_debug;

        /*
         * A wrapped for the device (both physical and logical), including some convenience functionality
         */
        Device m_device;

        /*
         * Creator and destructor
         */
        Display() = default;
        virtual ~Display() = default;

    protected:
        /*
         * Initializes GLFW and creates a window if none exists yet and sets the user pointer
         */
        void createWindow();

        /*
         * Creates the vulkan instance with the device extensions in Device and validation layers from VulkanDebug
         */
        void createInstance();

        /*
         * Creates the VulkanDebug member variable, which contains callbacks from vulkan, to aid in debugging
         */
        void createDebug();

        /*
         * Gets the required device extensions to be initialized by Vulkan. Could theoretically be overwritten depending on what you want to use the renderer for.
         */
        std::vector<const char*> getRequiredExtensions();
    public:
        /*
         * C++11 style singleton, returns an instance of the device class
         */
        static Display &get();

        /*
         * Initializes the display device and render window
         */
        void initialize();

        /*
         * Gets a references from the vulkan handle
         */
        vk::Instance &getVulkanInstance();

        /*
         * Gets a reference to the physical device
         */
        vk::PhysicalDevice& getPhysicalDevice();

        /*
         * Gets a reference to the logical device
         */
        vk::Device& getDevice();


        /*
         * Gets a reference to the wrapped device
         */
        Device& getWrappedDevice();

        void cleanup();

        void createDevice();

        void createSurface();

        int getDeviceScore(vk::PhysicalDevice p_physicalDevice);

        void createLogicalDevice(vk::PhysicalDevice p_device);
    };
}


#endif //VULKANENGINEFIXED_DISPLAY_HPP
