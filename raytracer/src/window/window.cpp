#include <iostream>
#include <vulkan/vulkan_core.h>

#include "window.hpp"

window::Window::Window(uint32_t width, uint32_t height)
{
    SDL_WindowFlags window_flags = (SDL_WindowFlags) SDL_WINDOW_VULKAN;

    this->sdl_window = SDL_CreateWindow(
        APPLICATION_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        window_flags
    );
}

window::Window::~Window()
{
    // Clean up SDL window
    SDL_DestroyWindow(this->sdl_window);
}

check::BasicResult window::Window::init_vulkan(VkInstance instance, VkSurfaceKHR *surface)
{
    return check::BasicResult::Ok;
}

