cmake_minimum_required(VERSION 3.20+)

# Use the latest C++ standard supported by CMake 3.20+
set(CMAKE_CXX_STANDARD 23)

project(VkVoxelRaytracer CXX)

# Include packages
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# Debugging flag (for enabling Vulkan validation layers and
# other debugging options)
if (DEBUGGING)
    add_definitions(-DDEBUGGING)
endif ()


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
set(${LIBS}
    ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${LIBS})
