#include "check.hpp"

check::BasicResult::BasicResult(Value value) : value(value) {}

constexpr check::BasicResult::operator check::BasicResult::Value() const
{
    return this->value;
} 

check::BasicResult::operator bool() const
{
    return this->value == BasicResult::Value::Ok;
}


template <typename ErrorInterface> 
void check::BasicResult::expect(std::string message)
{
    ErrorInterface::error(message);
}

void check::BasicResult::expect(std::string message)
{
    this->expect<error_interface::ThrowOnError>(message);
}


void check::BasicResult::fail(std::string message)
{
    BasicResult result = BasicResult::Value::Err;
    result.expect(message);
}

