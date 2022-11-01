#include "selector.hpp"

#include "raters/by_queue_family_support.hpp"
#include "raters/by_type.hpp"

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

std::vector<std::shared_ptr<rater::Rater>> physical::DeviceSelector::get_raters()
{
    std::vector<std::shared_ptr<rater::Rater>> raters;

    // RaterByType
    if (this->has_by_type())
        raters.push_back(std::make_shared<rater::RaterByType>());

    // RaterByQueueFamilySupport
    if (this->has_by_queue_family_support())
        raters.push_back(std::make_shared<rater::RaterByQueueFamilySupport>());
    
    return raters;
}

check::BasicResult physical::DeviceSelector::select(VkInstance instance, VkPhysicalDevice *device)
{
    // Get number of physical devices
    uint32_t device_count = 0;

    check::vk_check(vkEnumeratePhysicalDevices, instance, &device_count, nullptr)
        .expect("Failed to get number of physical devices");

    if (device_count == 0)
    {
        return check::BasicResult::Err;
    }

    // Get physical devices
    std::vector<VkPhysicalDevice> devices(device_count);

    check::vk_check(vkEnumeratePhysicalDevices, instance, &device_count, devices.data())
        .expect("Failed to enumerate physical devices");

    // Select device
    VkPhysicalDevice best_device = VK_NULL_HANDLE;
    int32_t best_rating = -1; 

    std::vector<std::shared_ptr<rater::Rater>> raters = this->get_raters();
    for (auto& device : devices)
    {
        // Rate the device
        int32_t device_rating = 0;
        for (auto& rater : raters)
        {
            device_rating += rater->rate_device(device);
        }

        if (device_rating > best_rating)
        {
            best_rating = device_rating;
            best_device = device;
        }
    }

    *device = best_device;

    return check::BasicResult::Ok;
}
