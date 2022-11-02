#include "vk_instance_info.hpp"

#include "../vulkan/debug/messenger.hpp"

#include <iostream>

check::BasicResult add_layer_name_if_supported(
        const char *layer, 
        std::vector<const char *>& layer_names, 
        std::vector<VkLayerProperties>& available_layers)
{
    bool supported = false;
    for (auto& available_layer : available_layers) {
        if (std::strcmp(available_layer.layerName, layer) == 0) {
            supported = true;
            break;
        }
    }

    if (supported) {
        layer_names.push_back(layer);
        return check::BasicResult::Ok;
    } else {
        return check::BasicResult::Err;
    }
}

void vk_instance_info::InstanceInfo::init_layers()
{
    // Add Khronos validation layer if running in debug mode
    // Get available layers
    uint32_t available_layers_count;
    vkEnumerateInstanceLayerProperties(&available_layers_count, nullptr);

    std::vector<VkLayerProperties> available_layers(available_layers_count);
    vkEnumerateInstanceLayerProperties(&available_layers_count, available_layers.data());

    std::cout << "Available Vulkan layers (" << available_layers_count << " in total):" << "\n";
    for (auto& available_layer : available_layers) {
        std::cout << available_layer.layerName << "\n";
    }
    std::cout << std::endl;

#ifdef DEBUGGING
    // Add VK_LAYER_KHRONOS_validation layer if supported
    add_layer_name_if_supported("VK_LAYER_KHRONOS_validation", this->layers, available_layers)
        .expect("VK_LAYER_KHRONOS_validation is not supported");
#endif
}

void vk_instance_info::InstanceInfo::init_extensions(SDL_Window *window)
{
    // Get extensions
    uint32_t extensions_count;
    SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, nullptr);

    // Get extensions
    this->extensions = std::vector<const char *>(extensions_count);
    SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, this->extensions.data());

    // Add debug utils extension if running in debug mode
#ifdef DEBUGGING
    this->extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

    // Output extensions
    std::cout << "Using Vulkan extensions:" << "\n";
    for (auto& extension : this->extensions) {
        std::cout << extension << "\n";
    }
    std::cout << std::endl;
}

vk_instance_info::InstanceInfo::InstanceInfo(const char *app_name, uint32_t app_version, SDL_Window *window)
{
    // Initialize VkApplicationInfo
    this->app_info = {};
    this->app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    this->app_info.pApplicationName = app_name;
    this->app_info.applicationVersion = app_version;
    this->app_info.pEngineName = "Internal engine";
    this->app_info.engineVersion = app_version;
    this->app_info.apiVersion = VK_API_VERSION_1_0;

    // Initialize VkInstanceCreateInfo
    this->create_info = {};
    this->create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    this->create_info.pApplicationInfo = &this->app_info;

    // Initialize extensions and layers
    this->init_layers();
    this->create_info.enabledLayerCount = this->layers.size();
    this->create_info.ppEnabledLayerNames = this->layers.data();
    this->init_extensions(window);
    this->create_info.enabledExtensionCount = this->extensions.size();
    this->create_info.ppEnabledExtensionNames = this->extensions.data();
    
#ifdef DEBUGGING 
    // Setup instance creation and destruction-level debug messenger in debug mode
    VkDebugUtilsMessengerCreateInfoEXT debug_create_info;
    debug::make_messenger_create_info(&debug_create_info);

    this->create_info.pNext = &debug_create_info;
#else
    // Otherwise, set pNext to a nullptr
    this->create_info.pNext = nullptr;
#endif
}

VkInstanceCreateInfo *vk_instance_info::InstanceInfo::create_info_ptr()
{
    return &this->create_info;
}

