#include <iostream>

#include "util/check.hpp"

#include "window/window.hpp"
#include "vulkan/debug/messenger.hpp"
#include "vulkan/device/physical/selector.hpp"

int main()
{
    // Create the window
    window::Window raytracer_window(800, 600);

    // Set up Vulkan
    VkInstance instance;
    VkSurfaceKHR surface;
    raytracer_window
        .init_vulkan(&instance, &surface)
        .expect("Failed to initialize raytracer instance");

#ifdef DEBUGGING
    // Setup debug messenger
    debug::DebugMessenger messenger;
    messenger.init(instance);
#endif
    
    // Select the best physical device to use
    VkPhysicalDevice physical_device;
   
    vulkan::device::physical::DeviceSelector selector = 
        vulkan::device::physical::DeviceSelector::build()
            .by_type()
            .by_queue_family_support();

    selector.select(instance, &physical_device)
        .expect("Failed to select suitable physical device");

#ifdef DEBUGGING
    // Get device properties
    VkPhysicalDeviceProperties device_props;
    vkGetPhysicalDeviceProperties(physical_device, &device_props);
    std::cout << "Selected best physical device: " << device_props.deviceName << std::endl;
#endif

#ifdef DEBUGGING
    // Destroy debug messenger
    messenger.destroy(instance);
#endif

    // Clean up Vulkan instance and surface
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyInstance(instance, NULL);

    return 0;
}
