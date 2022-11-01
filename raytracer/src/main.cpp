#include <iostream>

#include "util/check.hpp"
#include "window/window.hpp"
#include "vulkan/device/physical/selector.hpp"

int main()
{
    // Create the window
    window::Window raytracer_window(800, 600);

    // Set up Vulkan
    VkInstance instance;
    VkSurfaceKHR surface;
    raytracer_window.init_vulkan(instance, &surface)
        .expect("Failed to initialize raytracer instance");
    
    // Select the best physical device to use
    VkPhysicalDevice physical_device;
   
    vulkan::device::physical::DeviceSelector selector = 
        vulkan::device::physical::DeviceSelector::build()
            .by_type()
            .by_queue_family_support();

    selector.select(&physical_device)
        .expect("Failed to select suitable physical device");

    // Clean up Vulkan instance and surface
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyInstance(instance, NULL);

    return 0;
}
