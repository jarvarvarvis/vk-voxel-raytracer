#pragma once

#include <vulkan/vulkan.hpp>

namespace check
{
    class BasicResult
    {
    public:
        enum Value
        {
            Ok,
            Err
        };

        BasicResult() = default;
        constexpr BasicResult(Value value);

        constexpr operator Value() const;
        constexpr operator bool() const;

        void expect(std::string message);

    private:
        Value value;
    };

    template <typename F, typename... Args>
    BasicResult vk_check(F function, Args... args)
    {
        VkResult result = function(args...);
        if (result != VK_SUCCESS)
        {
            return BasicResult::Value::Err;
        }

        return BasicResult::Value::Ok;
    }
}

