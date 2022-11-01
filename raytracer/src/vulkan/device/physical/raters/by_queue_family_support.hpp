#pragma once

#include "../rater.hpp"

namespace rater
{
    class RaterByQueueFamilySupport : public Rater
    {
    public:
        constexpr RaterByQueueFamilySupport() = default;

        int32_t rate_device(VkPhysicalDevice device);
    };
}
