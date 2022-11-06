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

        VkDevice device;
        VkQueue graphics_queue;

    public:
        Context(vkb::Instance instance, VkSurfaceKHR surface);
        ~Context();

        check::BasicResult create_device_and_queue();
    };
}

