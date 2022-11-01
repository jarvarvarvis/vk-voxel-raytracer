#include <string>

namespace error_interface
{
    class ThrowOnError
    {
    public:
        ThrowOnError() = delete;
        static void error(std::string);
    };
}
