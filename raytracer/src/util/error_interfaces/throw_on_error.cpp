#include <stdexcept>

#include "throw_on_error.hpp"

void error_interface::ThrowOnError::error(std::string message)
{
    throw std::runtime_error(message);
}
