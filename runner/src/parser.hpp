#pragma once

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include "args.hpp"

namespace program_options = boost::program_options;

namespace parser
{
    class ArgumentParser
    {
    private:
        program_options::options_description allowed_options; 

    public:
        ArgumentParser();
        boost::optional<args::RaytracerArgs> parse(int argc, char *argv[]);
    };
}

