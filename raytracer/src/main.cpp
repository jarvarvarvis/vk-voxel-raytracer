#include <iostream>

#include "util/check.hpp"

#include "window/window.hpp"

int main()
{
    // Initialize SDL Video + Events instance
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        check::BasicResult::fail("Failed to initialize SDL");
    }

    // Create the window
    window::Window raytracer_window(800, 600);

    // Set up Vulkan
    VkInstance instance;
    VkSurfaceKHR surface;
    raytracer_window
        .init_vulkan(instance, &surface)
        .expect("Failed to initialize raytracer instance");

    // Clean up Vulkan instance and surface
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    return 0;
}
