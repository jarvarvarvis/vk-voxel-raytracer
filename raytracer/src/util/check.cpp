#include "check.hpp"

template <typename ErrorInterface> 
void check::BasicResult::expect(std::string message)
{
    ErrorInterface::error(message);
}

void check::BasicResult::expect(std::string message)
{
    this->expect<error_interface::ThrowOnError>(message);
}

template <typename ErrorInterface>
void check::BasicResult::fail(std::string message)
{
    BasicResult result = BasicResult::Err;
    result.expect<ErrorInterface>(message);
}

void check::BasicResult::fail(std::string message)
{
    BasicResult result = BasicResult::Err;
    result.expect(message);
}

