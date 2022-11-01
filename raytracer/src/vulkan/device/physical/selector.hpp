#pragma once

#include <vulkan/vulkan.hpp>

#include "../../../util/check.hpp"

#define FLAG(offset) (1 << offset)

namespace vulkan::device::physical
{
    enum class DeviceSelectorSpecifiers
    {
        None                 = 0,
        ByType               = FLAG(0),
        ByQueueFamilySupport = FLAG(1), 
    };

    inline DeviceSelectorSpecifiers operator|(DeviceSelectorSpecifiers a, DeviceSelectorSpecifiers b);
    inline DeviceSelectorSpecifiers& operator|=(DeviceSelectorSpecifiers& a, DeviceSelectorSpecifiers b);

    inline DeviceSelectorSpecifiers operator&(DeviceSelectorSpecifiers a, DeviceSelectorSpecifiers b);
    inline DeviceSelectorSpecifiers& operator&=(DeviceSelectorSpecifiers& a, DeviceSelectorSpecifiers b);

    class DeviceSelector
    {
    private:
        DeviceSelectorSpecifiers specifiers;

        constexpr DeviceSelector() : specifiers(DeviceSelectorSpecifiers::None) {};

    public:
        static DeviceSelector build();
        
        DeviceSelector& by_type();
        DeviceSelector& by_queue_family_support();

        bool has_by_type();
        bool has_by_queue_family_support();

        check::BasicResult select(VkPhysicalDevice *device);
    };
}
