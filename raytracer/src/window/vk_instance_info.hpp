#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include "../util/check.hpp"

namespace vk_instance_info
{
    class InstanceInfo
    {
    private:
        VkApplicationInfo app_info;
        VkInstanceCreateInfo create_info;

        std::vector<const char *> layers;
        std::vector<const char *> extensions;

        void init_layers();
        void init_extensions(SDL_Window *window);

    public:
        InstanceInfo(const char *app_name, uint32_t app_version, SDL_Window *window);

        check::BasicResult make_vulkan_instance(VkInstance *instance);

        VkInstanceCreateInfo *create_info_ptr();
    };
}
