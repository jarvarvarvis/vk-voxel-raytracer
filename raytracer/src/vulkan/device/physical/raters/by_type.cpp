#include "by_type.hpp"

#include <vulkan/vulkan.hpp>

int32_t rater::RaterByType::rate_device(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties device_props;
    vkGetPhysicalDeviceProperties(device, &device_props);

    int32_t rating = 0;

    // Discrete GPUs have a significant performance advantage
    if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        rating += 100;
    }
    // The next best option are integrated GPUs
    else if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
    {
        rating += 50;
    }
    // CPUs the are worst option 
    else if (device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
    {
        rating += 10;
    }

    return rating;
}

