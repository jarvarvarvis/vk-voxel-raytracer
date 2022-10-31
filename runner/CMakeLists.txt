cmake_minimum_required(VERSION 3.20+)

# Use the latest C++ standard supported by CMake 3.20+
set(CMAKE_CXX_STANDARD 23)

project(Runner CXX)


# Read source and header files in src/
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)

message("Found source files:\n" "${SOURCE_FILES}")
message("Found header files:\n" "${HEADER_FILES}")

# Create the executable
add_executable(${PROJECT_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES})

