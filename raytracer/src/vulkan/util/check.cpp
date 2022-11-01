#include "check.hpp"

constexpr check::BasicResult::BasicResult(Value value) : value(value) {}

constexpr check::BasicResult::operator check::BasicResult::Value() const
{
    return this->value;
}

constexpr check::BasicResult::operator bool() const
{
    return this->value == BasicResult::Value::Ok;
}

void check::BasicResult::expect(std::string message)
{
    if (this->value != BasicResult::Value::Ok)
    {
        throw std::runtime_error(message);
    }
}

