#include <iostream>
#include <vulkan/vulkan_core.h>

#include "vk_instance_info.hpp"
#include "window.hpp"

#include "../vulkan/debug/messenger.hpp"


window::Window::Window(uint32_t width, uint32_t height)
{
    this->sdl_window = SDL_CreateWindow(
        APPLICATION_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_VULKAN
    );

    this->vk_instance_info = std::make_unique<vk_instance_info::InstanceInfo>(
            APPLICATION_NAME, 
            VK_MAKE_VERSION(1, 0, 0),
            this->sdl_window
    );
}

window::Window::~Window()
{
    // Clean up SDL window
    SDL_DestroyWindow(this->sdl_window);
}

check::BasicResult window::Window::init_vulkan(VkInstance instance, VkSurfaceKHR *surface)
{
    // Create the instance
    VkInstanceCreateInfo *create_info = this->vk_instance_info->create_info_ptr();
    check::BasicResult instance_create_result = 
        check::vk_check(vkCreateInstance, create_info, nullptr, &instance);

    if (!instance_create_result) return instance_create_result;
    
    // Create the window surface
    SDL_bool surface_create_result = SDL_Vulkan_CreateSurface(this->sdl_window, instance, surface);

    if (!surface_create_result) {
        return check::BasicResult::Err;
    }

    return check::BasicResult::Ok;
}

