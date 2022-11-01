#include "window.hpp"

#include <iostream>

window::Window::Window(uint32_t width, uint32_t height)
{
    this->sdl_window = SDL_CreateWindow(
        APPLICATION_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_VULKAN
    );
}

window::Window::~Window()
{
    // Clean up SDL window
    SDL_DestroyWindow(this->sdl_window);
}

VkApplicationInfo window::Window::create_application_info()
{
    // Create app info
    VkApplicationInfo app_info;
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pNext = nullptr;
    app_info.pApplicationName = APPLICATION_NAME;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = APPLICATION_NAME " Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    return app_info;
}

VkInstanceCreateInfo window::Window::create_instance_create_info(VkApplicationInfo *app_info)
{
    // Initialize layers
    std::vector<const char *> layer_names {};

    // Add Khronos validation layer if running in debug mode
#ifdef DEBUGGING
    layer_names.push_back("VK_LAYER_KHRONOS_validation");
#endif

    // Get extensions
    uint32_t extensions_count;
    SDL_Vulkan_GetInstanceExtensions(this->sdl_window, &extensions_count, nullptr);

    // Get extensions
    std::vector<const char *> extension_names(extensions_count);
    SDL_Vulkan_GetInstanceExtensions(this->sdl_window, &extensions_count, extension_names.data());

#ifdef DEBUGGING
    std::cout << "Got Vulkan extensions:" << "\n";
    for (auto& extension : extension_names)
    {
        std::cout << extension << "\n";
    }
    std::cout << std::endl;
#endif


    // Create instance
    VkInstanceCreateInfo create_info {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = app_info;
    create_info.enabledLayerCount = layer_names.size();
    create_info.ppEnabledLayerNames = layer_names.data();
    create_info.enabledExtensionCount = extension_names.size();
    create_info.ppEnabledExtensionNames = extension_names.data();

    return create_info;
}

check::BasicResult window::Window::init_vulkan(VkInstance instance, VkSurfaceKHR *surface)
{
    // Create app info and instance create info
    VkApplicationInfo app_info = this->create_application_info();
    VkInstanceCreateInfo create_info = this->create_instance_create_info(&app_info);

    // Create the instance
    check::BasicResult result = check::vk_check(vkCreateInstance, &create_info, nullptr, &instance);
    if (result) return result;

    // Create the window surface
    SDL_bool res = SDL_Vulkan_CreateSurface(this->sdl_window, instance, surface);
    if (!res)
    {
        return check::BasicResult::Err;
    }

    return check::BasicResult::Ok;
}

