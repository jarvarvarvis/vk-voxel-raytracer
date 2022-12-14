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

        BasicResult() = delete;
        constexpr BasicResult(Value value) : value(value) {}

        constexpr operator Value() const
        {
            return this->value;
        }

        constexpr operator bool() const
        {
            return this->value == Ok;
        }

        constexpr BasicResult operator!() const
        {
            if (this->value == Ok)
                return Err;
            else
                return Ok;
        }

        // Specific error interface
        template <typename ErrorInterface>
        void expect(std::string message);

        // Default error interface
        void expect(std::string message);

        // Specific error interface
        template <typename ErrorInterface>
        static void fail(std::string message);

        // Default error interface
        static void fail(std::string message);

    private:
        Value value;
    };
    
    std::ostream& operator<<(std::ostream& os, BasicResult& result);

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

