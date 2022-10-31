cmake_minimum_required(VERSION 3.20+)

# Use the latest C++ standard supported by CMake 3.20+
set(CMAKE_CXX_STANDARD 23)

project(Runner CXX)

# Include packages
find_package(Boost 1.50 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Read source and header files in src/
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)

message("Found source files:\n" "${SOURCE_FILES}")
message("Found header files:\n" "${HEADER_FILES}")

# Create the executable
add_executable(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES})

# Link libraries
set(LIBS
    ${Boost_LIBRARIES})

message("Got libraries:\n" "${LIBS}")

target_link_libraries(${PROJECT_NAME} ${LIBS})

# Specify definitions
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    RAYTRACER_PATH="${CMAKE_SOURCE_DIR}/../raytracer/")

