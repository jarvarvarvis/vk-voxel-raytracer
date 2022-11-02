#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include "../definitions.hpp"
#include "../util/check.hpp"

#include "vk_instance_info.hpp"

namespace window
{
    class Window
    {
    private:
        SDL_Window *sdl_window;
        std::unique_ptr<vk_instance_info::InstanceInfo> vk_instance_info;

    public:
        Window(uint32_t width, uint32_t height);
        ~Window();

        check::BasicResult init_vulkan(VkInstance instance, VkSurfaceKHR *surface);
    };
}
