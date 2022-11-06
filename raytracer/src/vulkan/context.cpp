#include "context.hpp"

context::Context::Context(vkb::Instance instance, VkSurfaceKHR surface) :
    vk_instance(instance), window_surface(surface)
{}

context::Context::~Context()
{
    vkDestroySurfaceKHR(this->vk_instance.instance, this->window_surface, nullptr);
    vkb::destroy_device(this->device);
    vkb::destroy_instance(this->vk_instance);
}

check::BasicResult context::Context::select_physical_device()
{
    // Select physical devices
    vkb::PhysicalDeviceSelector selector(this->vk_instance);
    auto phys_device_ret = selector
        .set_surface(this->window_surface)
        .set_minimum_version(1, 1)
        .select();
    if (!phys_device_ret) {
        return check::BasicResult::Err;
    }

    this->physical_device = phys_device_ret.value();
    return check::BasicResult::Ok;
}

check::BasicResult context::Context::create_logical_device()
{
    // Build logical device
    vkb::DeviceBuilder device_builder { this->physical_device };
	auto device_ret = device_builder.build();
	if (!device_ret) {
        return check::BasicResult::Err;
	}

    this->device = device_ret.value();
    return check::BasicResult::Ok;
}

