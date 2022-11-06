#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>

#include <VkBootstrap.h>

#include "../definitions.hpp"
#include "../util/check.hpp"

namespace window
{
    class Window
    {
    private:
        SDL_Window *sdl_window;

        std::vector<const char *> get_sdl_vulkan_extensions();

    public:
        Window(uint32_t width, uint32_t height);
        ~Window();

        check::BasicResult init_vulkan(vkb::Instance *instance, VkSurfaceKHR *surface);
    };
}
