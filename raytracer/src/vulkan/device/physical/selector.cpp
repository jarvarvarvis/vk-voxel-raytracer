#include "selector.hpp"

namespace physical = vulkan::device::physical;

inline physical::DeviceSelectorSpecifiers physical::operator|(
        physical::DeviceSelectorSpecifiers a, 
        physical::DeviceSelectorSpecifiers b
) {
    return static_cast<physical::DeviceSelectorSpecifiers>(
        static_cast<long>(a) | static_cast<long>(b)
    );
}

inline physical::DeviceSelectorSpecifiers& physical::operator|=(
        physical::DeviceSelectorSpecifiers& a, 
        physical::DeviceSelectorSpecifiers b
) {
    long al = static_cast<long>(a);
    long bl = static_cast<long>(b);
    al |= bl;
    return a = static_cast<physical::DeviceSelectorSpecifiers>(al);
}

inline physical::DeviceSelectorSpecifiers physical::operator&(
        physical::DeviceSelectorSpecifiers a, 
        physical::DeviceSelectorSpecifiers b
) {
    return static_cast<physical::DeviceSelectorSpecifiers>(
        static_cast<long>(a) & static_cast<long>(b)
    );
}

inline physical::DeviceSelectorSpecifiers& physical::operator&=(
        physical::DeviceSelectorSpecifiers& a, 
        physical::DeviceSelectorSpecifiers b
) {
    long al = static_cast<long>(a);
    long bl = static_cast<long>(b);
    al &= bl;
    return a = static_cast<physical::DeviceSelectorSpecifiers>(al);
}


physical::DeviceSelector::DeviceSelector()
    : specifiers(DeviceSelectorSpecifiers::None)
{}

physical::DeviceSelector physical::DeviceSelector::build()
{
    return physical::DeviceSelector();
}

physical::DeviceSelector& physical::DeviceSelector::by_type()
{
    this->specifiers |= DeviceSelectorSpecifiers::ByType;
    return *this;
}

physical::DeviceSelector& physical::DeviceSelector::by_queue_family_support()
{
    this->specifiers |= DeviceSelectorSpecifiers::ByQueueFamilySupport;
    return *this;
}

bool physical::DeviceSelector::has_by_type()
{
    return static_cast<long>(this->specifiers & DeviceSelectorSpecifiers::ByType) == 1;
}

bool physical::DeviceSelector::has_by_queue_family_support()
{
    return static_cast<long>(this->specifiers & DeviceSelectorSpecifiers::ByQueueFamilySupport) == 1;
}

VkResult physical::DeviceSelector::select(VkPhysicalDevice *device)
{
    return VK_SUCCESS;
}
