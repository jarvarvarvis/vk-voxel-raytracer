#pragma once

#include <vulkan/vulkan.hpp>

namespace rater
{
    class Rater
    {
    public:
        constexpr Rater() = default;

        virtual int32_t rate_device(VkPhysicalDevice device) = 0;
    };
}
