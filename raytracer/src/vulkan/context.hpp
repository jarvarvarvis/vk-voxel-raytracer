#pragma once

#include <vulkan/vulkan.h>

#include <VkBootstrap.h>

#include "../util/check.hpp"

namespace context 
{
    class Context
    {
    private:
        vkb::Instance vk_instance;
        VkSurfaceKHR window_surface;

        vkb::PhysicalDevice physical_device;
        vkb::Device device;

    public:
        Context(vkb::Instance instance, VkSurfaceKHR surface);
        ~Context();

        check::BasicResult select_physical_device();
        check::BasicResult create_logical_device();
    };
}

