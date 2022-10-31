#pragma once

#include <istream>
#include <ostream>

namespace args
{
    enum class RaytracerBuildMode
    {
        Debug = 0,
        Release
    };

    // Override >> operator to read in RaytracerBuildModes from istreams
    std::istream& operator>>(std::istream& in, RaytracerBuildMode& mode);

    // Override << operator to write RaytracerBuildMode to ostream
    std::ostream& operator<<(std::ostream& out, const RaytracerBuildMode& mode);

    class RaytracerArgs
    {
    private:
        RaytracerBuildMode build_mode;
        bool should_build;

    public:
        RaytracerArgs(
            RaytracerBuildMode build_mode,
            bool should_build
        );

        RaytracerBuildMode mode();
        bool build();
    };
}

