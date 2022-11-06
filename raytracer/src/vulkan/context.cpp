#include "context.hpp"

context::Context::Context(vkb::Instance instance, VkSurfaceKHR surface) :
    vk_instance(instance), window_surface(surface)
{}

context::Context::~Context()
{
    vkDestroyDevice(this->device, nullptr);
    vkDestroySurfaceKHR(this->vk_instance.instance, this->window_surface, nullptr);
    vkb::destroy_instance(this->vk_instance);
}

check::BasicResult context::Context::create_device_and_queue()
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

    vkb::PhysicalDevice physical_device = phys_device_ret.value();

    // Build logical device
    vkb::DeviceBuilder device_builder { physical_device };
	auto device_ret = device_builder.build();
	if (!device_ret) {
        return check::BasicResult::Err;
	}

    vkb::Device vkb_device = device_ret.value();
    this->device = vkb_device.device;

    // Get the graphics queue
    auto graphics_queue_ret = vkb_device.get_queue(vkb::QueueType::graphics);
    if (!graphics_queue_ret) {
        return check::BasicResult::Err;
    }

    this->graphics_queue = graphics_queue_ret.value();
    return check::BasicResult::Ok;
}

VkDevice context::Context::get_device()
{
    return this->device;
}

VkQueue context::Context::get_graphics_queue()
{
    return this->graphics_queue;
}

