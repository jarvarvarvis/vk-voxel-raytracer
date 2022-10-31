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

    // Set build mode argument
    std::string build_mode_arg;
    if (build_mode == args::RaytracerBuildMode::Debug) {
        build_mode_arg = "debug";
    } else {
        build_mode_arg = "release";
    }

    // If it exists, run it
    if (bfs::exists(build_script_path)) {
        // Run process and read its stdout to the process_in stream
        bp::ipstream process_in;
        bp::child build_process("/bin/bash", build_script_path, build_mode_arg, bp::std_out > process_in);

        // Read process stdout
        std::string line;

        std::cout << "\nBuild script output:" << std::endl;
        while (build_process.running()) {
            std::getline(process_in, line);
            std::cout << line << std::endl;
        }
    } else {
        throw std::runtime_error(
            "The raytracer build script build.sh doesn't exist in the specified project path"
        );
    }
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
        bp::child raytracer_process(executable_path, bp::std_out > process_in);
       
        // Read process stdout
        std::string line;

        std::cout << "\nRaytracer output:" << std::endl;
        while (raytracer_process.running()) {
            std::getline(process_in, line);
            std::cout << line << std::endl;
        }
    } else {
        throw std::runtime_error(
                "The raytracer executable " RAYTRACER_EXECUTABLE " doesn't exist in the specified project path"
        );
    }
}
