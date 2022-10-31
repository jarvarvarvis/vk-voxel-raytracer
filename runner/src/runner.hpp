#include "args.hpp"

namespace runner
{
    class Runner
    {
    private:
        std::string raytracer_project_path;

    public:
        Runner(std::string raytracer_project_path);

        void build(args::RaytracerBuildMode build_mode);
        void run();
    };
}
