#pragma once

#include "../rater.hpp"

namespace rater
{
    class RaterByType : public Rater
    {
    public:
        constexpr RaterByType() = default; 

        int32_t rate_device(VkPhysicalDevice device);
    };
}

