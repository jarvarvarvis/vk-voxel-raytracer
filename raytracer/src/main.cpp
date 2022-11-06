#include <iostream>
#include <sstream>

#include "util/check.hpp"
#include "vulkan/context.hpp"

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
    vkb::Instance instance;
    VkSurfaceKHR surface;
    raytracer_window
        .init_vulkan(&instance, &surface)
        .expect("Failed to initialize raytracer instance");

    // Create the Vulkan context
    context::Context context(instance, surface);
    context.select_physical_device()
        .expect("Failed to select physical device");
    context.create_logical_device()
        .expect("Failed to create logical device");

    return 0;
}
