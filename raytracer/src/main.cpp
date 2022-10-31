#include <iostream>

#include "window/window.hpp"

int main()
{
    // Create the window
    window::Window raytracer_window(800, 600);

    // Set up Vulkan
    VkInstance instance;
    VkSurfaceKHR surface;
    if (raytracer_window.init_vulkan(instance, &surface) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to initialise Vulkan instance and/or surface");
    }

    return 0;
}
