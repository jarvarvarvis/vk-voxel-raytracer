#pragma once

#include <vulkan/vulkan_core.h>

#include "../../util/check.hpp"

namespace debug
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL
    debug_callback(
            VkDebugUtilsMessageSeverityFlagBitsEXT severity,
            unsigned int type,
            const VkDebugUtilsMessengerCallbackDataEXT *callback_data,
            void *user_data
    );
    
    void make_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT *create_info,
                                           void *user_data = nullptr);

    class DebugMessenger
    {
    private:
        VkDebugUtilsMessengerCreateInfoEXT create_info;
        VkDebugUtilsMessengerEXT debug_messenger;

    public:
        DebugMessenger(void *user_data = nullptr);
        check::BasicResult init(VkInstance instance, 
                                const VkAllocationCallbacks *allocator = nullptr);
        check::BasicResult destroy(VkInstance instance,
                                   const VkAllocationCallbacks *allocator = nullptr);
    };
}

