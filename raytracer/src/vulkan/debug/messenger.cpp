#include <iostream>

#include <SDL2/SDL_vulkan.h>

#include "messenger.hpp"

VkBool32 debug::debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity, 
        unsigned int type, 
        const VkDebugUtilsMessengerCallbackDataEXT *callback_data, 
        void *user_data
)
{
    std::cout << "Received message: \n" << callback_data->pMessage << "\n" << std::endl;
    return VK_FALSE;
}

void debug::make_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT *create_info,
                                       void *user_data)
{
	create_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	create_info->flags = 0;
	create_info->pNext = nullptr;
    create_info->pUserData = user_data;
	create_info->messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	create_info->messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
	create_info->pfnUserCallback = debug::debug_callback;
}

debug::DebugMessenger::DebugMessenger(void *user_data)
{
    this->create_info = {};
    this->debug_messenger = {};
    debug::make_messenger_create_info(&this->create_info, user_data);

    // Get the function pointer to vkGetInstanceProcAddr
    this->get_instance_proc_addr = (PFN_vkGetInstanceProcAddr) SDL_Vulkan_GetVkGetInstanceProcAddr();
}

check::BasicResult debug::DebugMessenger::init(VkInstance instance,
                                               const VkAllocationCallbacks *allocator)
{
    std::cout << "Trying to acquire vkCreateDebugUtilsMessengerEXT" << std::endl;

    // Get the vkCreateDebugUtilsMessengerEXT function pointer
    PFN_vkCreateDebugUtilsMessengerEXT create_debug_utils_messenger =
        (PFN_vkCreateDebugUtilsMessengerEXT)
            this->get_instance_proc_addr(instance, "vkCreateDebugUtilsMessengerEXT");

    std::cout << "Acquired vkCreateDebugUtilsMessengerEXT? " << create_debug_utils_messenger << std::endl;

    if (create_debug_utils_messenger != nullptr) {
        // Create debug utils messenger
        VkResult result = create_debug_utils_messenger(instance, 
                &this->create_info, 
                allocator, 
                &this->debug_messenger);
        
        if (result != VK_SUCCESS)
            return check::BasicResult::Err;

        return check::BasicResult::Ok;
    } else {
        return check::BasicResult::Err;
    }
}

check::BasicResult debug::DebugMessenger::destroy(VkInstance instance,
                                                  const VkAllocationCallbacks *allocator)
{
    PFN_vkDestroyDebugUtilsMessengerEXT destroy_debug_utils_messenger =
        (PFN_vkDestroyDebugUtilsMessengerEXT) 
            this->get_instance_proc_addr(instance, "vkDestroyDebugUtilsMessengerEXT");
    
    std::cout << "Acquired vkDestroyDebugUtilsMessengerEXT? " << destroy_debug_utils_messenger << std::endl;

    if (destroy_debug_utils_messenger != nullptr) {
        // Destroy debug utils messenger
        destroy_debug_utils_messenger(instance, this->debug_messenger, allocator);
        return check::BasicResult::Ok;
    } else {
        return check::BasicResult::Err;
    }
}

