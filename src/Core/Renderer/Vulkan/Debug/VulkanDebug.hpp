//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_VULKANDEBUG_HPP
#define VULKANENGINEFIXED_VULKANDEBUG_HPP

#include <vector>
#include <vulkan/vulkan.hpp>

namespace mt
{
    class VulkanDebug
    {
    private:
        vk::DebugReportCallbackEXT m_callback;
        vk::Instance               m_instance;

    public:

        static const bool m_enableValidationLayers;
        static const std::vector<const char*> m_validationLayers;

    private:

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugReportFlagsEXT p_flags,
                VkDebugReportObjectTypeEXT p_objType,
                uint64_t p_obj,
                size_t p_location,
                int32_t p_code,
                const char* p_layerPrefix,
                const char* p_msg,
                void* p_userData);

        inline void printDebug(vk::DebugReportFlagsEXT p_flags,
                               vk::DebugReportObjectTypeEXT p_typeFlags,
                               int32_t p_code,
                               const char* p_layerPrefix,
                               const char* p_message);

        vk::Result createDebugReportCallbackEXT(vk::Instance p_instance,
                                                const vk::DebugReportCallbackCreateInfoEXT* p_createInfo,
                                                const vk::AllocationCallbacks* p_allocator,
                                                vk::DebugReportCallbackEXT* p_callback);

        void destroyDebugReportCallbackEXT(vk::Instance p_instance,
                                           vk::DebugReportCallbackEXT p_callback,
                                           const vk::AllocationCallbacks* p_allocator);


    public:
        void create(vk::Instance p_instance);

        void destroy();

        bool checkValidationLayerSupport();
    };
}


#endif //VULKANENGINEFIXED_VULKANDEBUG_HPP
