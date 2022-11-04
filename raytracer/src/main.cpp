#include <iostream>
#include <sstream>

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
    vkb::Instance instance;
    VkSurfaceKHR surface;
    raytracer_window
        .init_vulkan(&instance, &surface)
        .expect("Failed to initialize raytracer instance");

    // Select physical devices
    vkb::PhysicalDeviceSelector selector(instance);
    auto phys_device_ret = selector
        .set_surface(surface)
        .set_minimum_version(1, 1)
        .select();
    if (!phys_device_ret) {
        std::ostringstream msg;
        msg << "Failed to select suitable physical device: ";
        msg << phys_device_ret.error().message();
        check::BasicResult::fail(msg.str());
    }
    vkb::PhysicalDevice physical_device = phys_device_ret.value();

    // Build logical device
    vkb::DeviceBuilder device_builder { physical_device };
	auto device_ret = device_builder.build();
	if (!device_ret) {
        std::ostringstream msg;
        msg << "Failed to create logical device: ";
		msg << device_ret.error().message() << "\n";
        check::BasicResult::fail(msg.str());
	}
    vkb::Device device = device_ret.value();

    // Clean up
    vkDestroySurfaceKHR(instance.instance, surface, nullptr);
    vkb::destroy_device(device);
    vkb::destroy_instance(instance);

    return 0;
}
