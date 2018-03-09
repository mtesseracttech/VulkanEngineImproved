//
// Created by MTesseracT on 8-3-2018.
//

#ifndef VULKANENGINEFIXED_DISPLAY_HPP
#define VULKANENGINEFIXED_DISPLAY_HPP

#include <vulkan/vulkan.hpp>
#include <Core/Renderer/Vulkan/Debug/VulkanDebug.hpp>

namespace mt
{
    class Display
    {
    private:
        //The vulkan instance
        vk::Instance m_instance = nullptr;
        VulkanDebug m_debug;


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

        std::vector<const char*> getRequiredExtensions();

    public:
        /*
         * C++11 Style Singleton, returns an instance of the device class
         */
        static Display &get();

        /*
         * Initializes the display device and render window
         */
        void Initialize();

        vk::Instance &getVulkanInstance();

        void createDebug();
    };
}


#endif //VULKANENGINEFIXED_DISPLAY_HPP
