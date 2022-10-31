#include <iostream>

#include "definitions.hpp"

#include "args.hpp"
#include "parser.hpp"
#include "runner.hpp"

int main(int argc, char *argv[]) {
    parser::ArgumentParser args_parser;
    boost::optional<args::RaytracerArgs> parsed_args = args_parser.parse(argc, argv);

    // Exit when args have a none value
    if (parsed_args == boost::none)
        return 0;

    std::cout << "Raytracer project found in " << RAYTRACER_PATH << "\n";

    // Create runner
    runner::Runner runner(RAYTRACER_PATH);

    // Build or run, based on args
    args::RaytracerArgs args = parsed_args.value();
    if (args.build()) {
        std::cout << "Building raytracer, mode = " << args.mode() << "\n";
        runner.build(args.mode());
    } else {
        std::cout << "Running raytracer" << "\n";
        runner.run(args.mode());
    }

    return 0;
}
