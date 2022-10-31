#pragma once

#include <vulkan/vulkan.hpp>

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

        DeviceSelector();

    public:
        static DeviceSelector build();
        
        DeviceSelector& by_type();
        DeviceSelector& by_queue_family_support();

        bool has_by_type();
        bool has_by_queue_family_support();

        VkResult select(VkPhysicalDevice *device);
    };
}
