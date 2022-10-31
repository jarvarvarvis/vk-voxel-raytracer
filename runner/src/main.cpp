#include <iostream>

#include "args.hpp"
#include "parser.hpp"

int main(int argc, char* argv[])
{
    parser::ArgumentParser args_parser;
    boost::optional<args::RaytracerArgs> args = args_parser.parse(argc, argv);

    if (args.is_initialized()) {
        std::cout << "Mode = " << args.value().mode() << "\n";
    }

    return 0;
}

