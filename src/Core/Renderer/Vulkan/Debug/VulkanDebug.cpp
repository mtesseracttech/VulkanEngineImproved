//
// Created by MTesseracT on 9-3-2018.
//

#include <iostream>
#include <Core/Utility/Logger.hpp>
#include "VulkanDebug.hpp"

namespace mt
{
    void VulkanDebug::create(vk::Instance p_instance)
    {
        assert(p_instance);

        m_instance = p_instance;

        if (!getEnableValidationLayers()) return;

        vk::DebugReportCallbackCreateInfoEXT callbackCreateInfo;
        callbackCreateInfo.flags = vk::DebugReportFlagBitsEXT::eWarning |
                                   vk::DebugReportFlagBitsEXT::ePerformanceWarning |
                                   vk::DebugReportFlagBitsEXT::eError |
                                   vk::DebugReportFlagBitsEXT::eDebug;
        callbackCreateInfo.pfnCallback = debugCallback;
        callbackCreateInfo.pUserData = this;

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
                                 const char *p_layerPrefix,
                                 const char *p_message)
    {
        if (p_reportflags & vk::DebugReportFlagBitsEXT::eError)
        {
            std::cerr << "[VK-ERR][" << p_layerPrefix << "] " << p_code << " - " << p_message
                      << std::endl;
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eWarning)
        {
            std::cerr << "[VK-WRN][" << p_layerPrefix << "] " << p_code << " - " << p_message
                      << std::endl;
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::ePerformanceWarning)
        {
            std::cerr << "[VK-PRF][" << p_layerPrefix << "] " << p_code << " - " << p_message
                      << std::endl;
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eInformation)
        {
            std::cout << "[VK-INF][" << p_layerPrefix << "] " << p_code << " - " << p_message
                      << std::endl;
        }
        else if (p_reportflags & vk::DebugReportFlagBitsEXT::eDebug)
        {
            std::cout << "[VK-DBG][" << p_layerPrefix << "] " << p_code << " - " << p_message
                      << std::endl;
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebug::debugCallback(VkDebugReportFlagsEXT p_flags,
                                                              VkDebugReportObjectTypeEXT p_objType,
                                                              uint64_t p_obj,
                                                              size_t p_location,
                                                              int32_t p_code,
                                                              const char *p_layerPrefix,
                                                              const char *p_msg,
                                                              void *p_userData)
    {
        auto flags = vk::DebugReportFlagBitsEXT(p_flags);
        auto objType = vk::DebugReportObjectTypeEXT(p_objType);

        auto debugCaller = reinterpret_cast<VulkanDebug *>(p_userData);

        debugCaller->printDebug(flags, objType, p_code, p_layerPrefix, p_msg);

        return VK_FALSE;
    }

    vk::Result VulkanDebug::createDebugReportCallbackEXT(vk::Instance p_instance,
                                                         const vk::DebugReportCallbackCreateInfoEXT *p_createInfo,
                                                         const vk::AllocationCallbacks *p_allocator,
                                                         vk::DebugReportCallbackEXT *p_callback)
    {
        auto instance = static_cast<VkInstance>(p_instance);
        auto createInfo = reinterpret_cast<const VkDebugReportCallbackCreateInfoEXT *>(p_createInfo);
        auto allocator = reinterpret_cast<const VkAllocationCallbacks *>(p_allocator);
        auto callback = reinterpret_cast<VkDebugReportCallbackEXT *>(p_callback);
        auto func = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(p_instance.getProcAddr(
                "vkCreateDebugReportCallbackEXT"));

        if (func) return vk::Result(func(instance, createInfo, allocator, callback));
        return vk::Result::eErrorExtensionNotPresent;
    }

    void VulkanDebug::destroyDebugReportCallbackEXT(vk::Instance p_instance,
                                                    vk::DebugReportCallbackEXT p_callback,
                                                    const vk::AllocationCallbacks *p_allocator)
    {
        auto instance = static_cast<VkInstance>(p_instance);
        auto allocator = reinterpret_cast<const VkAllocationCallbacks *>(p_allocator);
        auto callback = static_cast<VkDebugReportCallbackEXT>(p_callback);
        auto func = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(p_instance.getProcAddr(
                "vkDestroyDebugReportCallbackEXT"));

        if (func) func(instance, callback, allocator);
    }

    bool VulkanDebug::getEnableValidationLayers()
    {
        return m_enableValidationLayers;
    }

    const std::vector<const char *>& VulkanDebug::getValidationLayers()
    {
        return m_validationLayers;
    }

    bool VulkanDebug::checkValidationLayerSupport()
    {
        std::vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();

        for (const char *layerName : m_validationLayers)
        {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers)
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
}