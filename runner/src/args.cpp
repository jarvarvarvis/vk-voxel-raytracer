#include "args.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>

std::istream& args::operator>>(std::istream& in, args::RaytracerBuildMode& mode)
{
    // Read token from istream
    std::string token;
    in >> token;

    boost::to_lower(token);

    if (token == "debug") {
        mode = args::RaytracerBuildMode::Debug;
    }
    else if (token == "release") {
        mode = args::RaytracerBuildMode::Release;
    } 
    else {
        using validation_error = boost::program_options::validation_error;
        throw validation_error(validation_error::kind_t::invalid_option_value);
    }

    return in;
}

std::ostream& args::operator<<(std::ostream& out, const args::RaytracerBuildMode& mode)
{
    if (mode == args::RaytracerBuildMode::Debug) {
        out << "RaytracerBuildMode::Debug";
    } else if (mode == args::RaytracerBuildMode::Release) {
        out << "RaytracerBuildMode::Release"; 
    }

    return out;
}

args::RaytracerArgs::RaytracerArgs(args::RaytracerBuildMode build_mode, bool should_build) :
    build_mode(build_mode),
    should_build(should_build)
{
}

args::RaytracerBuildMode args::RaytracerArgs::mode() { return this->build_mode; }

bool args::RaytracerArgs::build() { return this->should_build; }
