#include <iostream>

#include "args.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
    parser::ArgumentParser args_parser;
    boost::optional<args::RaytracerArgs> parsed_args = args_parser.parse(argc, argv);

    // Exit when args have a none value
    if (parsed_args == boost::none)
        return 0;

    args::RaytracerArgs args = parsed_args.value();
    if (args.build()) {
        std::cout << "Building raytracer, mode = " << args.mode() << "\n";
    } else {
        std::cout << "Running raytracer" << "\n";
    }

    return 0;
}
