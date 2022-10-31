#include "runner.hpp"
#include "definitions.hpp"

#include <iostream>
#include <boost/process.hpp>

namespace bfs = boost::filesystem;
namespace bp  = boost::process;

runner::Runner::Runner(std::string raytracer_project_path) : 
    raytracer_project_path(raytracer_project_path)
{

}

void runner::Runner::build(args::RaytracerBuildMode build_mode)
{
    bfs::path project_path = this->raytracer_project_path;
    bfs::path build_script_path = project_path / "build.sh";
}

void runner::Runner::run(args::RaytracerBuildMode build_mode)
{
    // Get path to the executable
    bfs::path project_path = this->raytracer_project_path;
    bfs::path executable_path = project_path/"build";
    if (build_mode == args::RaytracerBuildMode::Debug) {
        executable_path = executable_path/"debug"/RAYTRACER_EXECUTABLE;
    } else {
        executable_path = executable_path/"release"/RAYTRACER_EXECUTABLE;
    }

    // If it exists, run it
    if (bfs::exists(executable_path)) {
        // Run process and read its stdout to the process_in stream
        bp::ipstream process_in;
        bp::child raytracer(executable_path, bp::std_out > process_in);
       
        // Read input from process
        std::string line;

        std::cout << "\nRaytracer output:" << std::endl;
        while (raytracer.running()) {
            std::getline(process_in, line);
            std::cout << line << std::endl;
        }
    } else {
        throw std::runtime_error(
                "The raytracer executable " RAYTRACER_EXECUTABLE " doesn't exist in the specified project path"
        );
    }
}
