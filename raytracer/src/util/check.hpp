#pragma once

#include <vulkan/vulkan.hpp>

#include "error_interfaces/throw_on_error.hpp"

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
        BasicResult(Value value);

        constexpr operator Value() const;
        explicit operator bool() const;

        // Specific error interface
        template <typename ErrorInterface>
        void expect(std::string message);

        // Default error interface
        void expect(std::string message);

        static void fail(std::string message);

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

