#include <iostream>

#include "parser.hpp"
#include "args.hpp"

parser::ArgumentParser::ArgumentParser() :
    allowed_options("Allowed options")
{
    // Add command line options
    auto add = this->allowed_options.add_options();
    add("help", "Produce help message");
    add("mode", program_options::value<args::RaytracerBuildMode>(), "Build mode, Debug is the default");
}

boost::optional<args::RaytracerArgs> parser::ArgumentParser::parse(int argc, char *argv[])
{
    // Parse command line arguments
    program_options::variables_map vmap;
    program_options::store(
            program_options::parse_command_line(argc, argv, this->allowed_options), 
            vmap
    );
    program_options::notify(vmap);

    // Get arguments
    // When the help flag is specified, quit and print usage
    if (vmap.count("help")) {
        std::cout << this->allowed_options << std::endl;
        return boost::none;
    }

    // Parse arguments
    // Get build mode
    args::RaytracerBuildMode mode;

    if (vmap.count("mode")) {
        mode = vmap["mode"].as<args::RaytracerBuildMode>();
    } else {
        mode = args::RaytracerBuildMode::Debug;
    }

    // Return arguments
    return args::RaytracerArgs(mode);
}

