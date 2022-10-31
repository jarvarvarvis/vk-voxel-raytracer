#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "../definitions.hpp"

namespace window
{
    class Window
    {
    private:
        SDL_Window *sdl_window;

    public:
        Window(uint32_t width, uint32_t height);
        ~Window();

        VkApplicationInfo create_application_info();
        VkInstanceCreateInfo create_instance_create_info(VkApplicationInfo *app_info);
        VkResult init_vulkan(VkInstance instance, VkSurfaceKHR *surface);
    };
}
