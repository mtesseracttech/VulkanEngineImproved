//
// Created by MTesseracT on 9-3-2018.
//

#include <iostream>
#include <Core/Utility/Logger.hpp>
#include <sstream>
#include <map>
#include "VulkanDebug.hpp"

namespace mt
{

#ifdef NDEBUG
    const bool VulkanDebug::m_enableValidationLayers = false;
#else
    const bool VulkanDebug::m_enableValidationLayers = true;
#endif //NDEBUG


    const std::vector<const char*> VulkanDebug::m_validationLayers = {
#ifdef _WIN32 //Because thus far I only got these layers to work on Windows
            "VK_LAYER_LUNARG_standard_validation"
#endif //__MINGW32__
    };


    void VulkanDebug::create(vk::Instance p_instance)
    {
        assert(p_instance);

        m_instance = p_instance;

        if (!m_enableValidationLayers) return;

        vk::DebugReportCallbackCreateInfoEXT callbackCreateInfo;
        callbackCreateInfo.flags       = vk::DebugReportFlagBitsEXT::eWarning |
                                         vk::DebugReportFlagBitsEXT::ePerformanceWarning |
                                         vk::DebugReportFlagBitsEXT::eError |
                                         vk::DebugReportFlagBitsEXT::eDebug;
        callbackCreateInfo.pfnCallback = debugCallback;
        callbackCreateInfo.pUserData   = this;

        if (createDebugReportCallbackEXT(p_instance, &callbackCreateInfo, nullptr, &m_callback) != vk::Result::eSuccess)
        {
            throw std::runtime_error("failed to set up debug callback!");
        }

    }

    void VulkanDebug::destroy()
    {
        destroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
        m_callback = nullptr;
        m_instance = nullptr;
    }


    void VulkanDebug::printDebug(vk::DebugReportFlagsEXT p_reportflags,
                                 vk::DebugReportObjectTypeEXT p_objectFlags,
                                 int32_t p_code,
                                 const char* p_layerPrefix,
                                 const char* p_message)
    {
        std::stringstream msg;
        msg << "[VK-" << p_layerPrefix << "][" << getDebugObjectName(p_objectFlags) << "] (" << p_code << ") - "
            << p_message;

        if (p_reportflags & vk::DebugReportFlagBitsEXT::eError)
        {
            throw std::runtime_error(msg.str());
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eWarning)
        {
            Logger::log(msg.str(), LogError);
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::ePerformanceWarning)
        {
            Logger::log(msg.str(), LogError);
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eInformation)
        {
            Logger::log(msg.str(), LogInfo);
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eDebug)
        {
            Logger::log(msg.str(), LogDebug);
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebug::debugCallback(VkDebugReportFlagsEXT p_flags,
                                                              VkDebugReportObjectTypeEXT p_objType,
                                                              uint64_t p_obj,
                                                              size_t p_location,
                                                              int32_t p_code,
                                                              const char* p_layerPrefix,
                                                              const char* p_msg,
                                                              void* p_userData)
    {
        auto flags   = vk::DebugReportFlagBitsEXT(p_flags);
        auto objType = vk::DebugReportObjectTypeEXT(p_objType);

        auto debugCaller = reinterpret_cast<VulkanDebug*>(p_userData);

        debugCaller->printDebug(flags, objType, p_code, p_layerPrefix, p_msg);

        return VK_FALSE;
    }

    vk::Result VulkanDebug::createDebugReportCallbackEXT(vk::Instance p_instance,
                                                         const vk::DebugReportCallbackCreateInfoEXT* p_createInfo,
                                                         const vk::AllocationCallbacks* p_allocator,
                                                         vk::DebugReportCallbackEXT* p_callback)
    {
        auto instance   = static_cast<VkInstance>(p_instance);
        auto createInfo = reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT*>(p_createInfo);
        auto allocator  = reinterpret_cast<const VkAllocationCallbacks*>(p_allocator);
        auto callback   = reinterpret_cast<VkDebugReportCallbackEXT*>(p_callback);
        auto func       = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(p_instance.getProcAddr(
                "vkCreateDebugReportCallbackEXT"));

        if (func) return vk::Result(func(instance, createInfo, allocator, callback));
        return vk::Result::eErrorExtensionNotPresent;
    }

    void VulkanDebug::destroyDebugReportCallbackEXT(vk::Instance p_instance,
                                                    vk::DebugReportCallbackEXT p_callback,
                                                    const vk::AllocationCallbacks* p_allocator)
    {
        auto instance  = static_cast<VkInstance>(p_instance);
        auto allocator = reinterpret_cast<const VkAllocationCallbacks*>(p_allocator);
        auto callback  = static_cast<VkDebugReportCallbackEXT>(p_callback);
        auto func      = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(p_instance.getProcAddr(
                "vkDestroyDebugReportCallbackEXT"));

        if (func) func(instance, callback, allocator);
    }

    bool VulkanDebug::checkValidationLayerSupport()
    {
        std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();

        for (const char* layerName : m_validationLayers)
        {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers)
            {
                if (strcmp(layerName, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) return false;
        }
        return true;
    }

    std::string VulkanDebug::getDebugObjectName(vk::DebugReportObjectTypeEXT p_type)
    {
        const std::map<vk::DebugReportObjectTypeEXT, const std::string> names{
                std::make_pair(vk::DebugReportObjectTypeEXT::eUnknown, "Unknown"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eInstance, "Instance"),
                std::make_pair(vk::DebugReportObjectTypeEXT::ePhysicalDevice, "Physical Device"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDevice, "Logical Device"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eQueue, "Queue"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eSemaphore, "Semaphore"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eCommandBuffer, "Command Buffer"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eFence, "Fence"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDeviceMemory, "Device Memory"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eBuffer, "Buffer"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eImage, "Image"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eEvent, "Event"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eQueryPool, "Query Pool"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eBufferView, "Buffer View"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eImageView, "Image View"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eShaderModule, "Shader Module"),
                std::make_pair(vk::DebugReportObjectTypeEXT::ePipelineCache, "Pipeline Cache"),
                std::make_pair(vk::DebugReportObjectTypeEXT::ePipelineLayout, "Pipeline Layout"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eRenderPass, "Render Pass"),
                std::make_pair(vk::DebugReportObjectTypeEXT::ePipeline, "Pipeline"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDescriptorSetLayout, "Descriptor Set Layout"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eSampler, "Sampler"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDescriptorPool, "Descriptor Pool"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDescriptorSet, "Descriptor Set"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eFramebuffer, "Frame Buffer"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eCommandPool, "Command Pool"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eSurfaceKhr, "Surface KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eSwapchainKhr, "Swapchain KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDisplayKhr, "Display KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDisplayModeKhr, "Display Mode KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDebugReportCallbackExt, "Debug Report Callback EXT"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eDescriptorUpdateTemplateKHR,
                               "Descriptor Update Template KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eObjectTableNvx, "Object Table NVX"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eIndirectCommandsLayoutNvx,
                               "Indirect Commands Layout NVX"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eSamplerYcbcrConversionKHR,
                               "Sampler YCbCr Conversion KHR"),
                std::make_pair(vk::DebugReportObjectTypeEXT::eValidationCacheExt, "Validation Cache EXT")
        };
        return names.at(p_type);
    }
}