cmake_minimum_required(VERSION 3.20+)

# Use the latest C++ standard supported by CMake 3.20+
set(CMAKE_CXX_STANDARD 23)

project(VkVoxelRaytracer CXX)

# Include packages
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

# Debugging flag (for enabling Vulkan validation layers and
# other debugging options)
if (DEBUGGING)
    add_definitions(-DDEBUGGING)
    set(CMAKE_BUILD_TYPE Debug)
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

# Fetch git libraries
include(FetchContent)

# vk-bootstrap
FetchContent_Declare(
    fetch_vk_bootstrap
    GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap
    GIT_TAG        v0.11
)
FetchContent_MakeAvailable(fetch_vk_bootstrap)

# Link libraries
set(LIBS
    Vulkan::Vulkan
    SDL2::SDL2
    vk-bootstrap::vk-bootstrap)

message("Got libraries:\n" ${LIBS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})

# Specify definitions
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    APPLICATION_NAME="${PROJECT_NAME}")

