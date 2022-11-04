#include <SDL2/SDL_vulkan.h>
#include <iostream>
#include <vulkan/vulkan_core.h>

#include "window.hpp"

window::Window::Window(uint32_t width, uint32_t height)
{
    SDL_WindowFlags window_flags = (SDL_WindowFlags) SDL_WINDOW_VULKAN;

    this->sdl_window = SDL_CreateWindow(
        APPLICATION_NAME,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        window_flags
    );
}

window::Window::~Window()
{
    // Clean up SDL window
    SDL_DestroyWindow(this->sdl_window);
}

std::vector<const char *> window::Window::get_sdl_vulkan_extensions()
{
    uint32_t extensions_count;
    SDL_Vulkan_GetInstanceExtensions(this->sdl_window, &extensions_count, nullptr);

    std::vector<const char *> extensions(extensions_count);
    SDL_Vulkan_GetInstanceExtensions(this->sdl_window, &extensions_count, extensions.data());

    return extensions;
}

check::BasicResult window::Window::init_vulkan(vkb::Instance *instance, VkSurfaceKHR *surface)
{
    // Initialize builder
    vkb::InstanceBuilder builder;
    builder = builder.set_app_name(APPLICATION_NAME);

    // Enable validation layers and debug messenger
#ifdef DEBUGGING
    builder = builder.request_validation_layers()
        .use_default_debug_messenger();
#endif

    // Enable extensions required by SDL
    std::vector<const char *> extensions = this->get_sdl_vulkan_extensions();
    std::cout << "Enabled extensions (" << extensions.size() << " in total):" << "\n";
    for (auto& extension: extensions)
    {
        std::cout << " - " << extension << "\n";
        builder = builder.enable_extension(extension);
    }
    std::cout << std::endl;

    // Build the instance
    auto inst_ret = builder.build();

    if (!inst_ret) {
        return check::BasicResult::Err;
    }

    *instance = inst_ret.value();

    // Create the window surface
    SDL_bool res = SDL_Vulkan_CreateSurface(this->sdl_window, instance->instance, surface);
    if (!res) {
        *surface = nullptr;

        const char *error = SDL_GetError();
        std::cout << "Failed to initialize window surface: " << error << std::endl;

        return check::BasicResult::Err;
    }

    return check::BasicResult::Ok;
}

