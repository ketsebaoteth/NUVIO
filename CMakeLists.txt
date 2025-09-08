cmake_minimum_required(VERSION 3.16)
project(NUVIO)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

find_package(OpenGL REQUIRED)

# Recursively find all header files in includes/
file(GLOB_RECURSE PROJECT_HEADERS
    "${CMAKE_SOURCE_DIR}/includes/**/*.h"
    "${CMAKE_SOURCE_DIR}/includes/**/*.hpp"
    "${CMAKE_SOURCE_DIR}/includes/internal/**/*.hpp"
    "${CMAKE_SOURCE_DIR}/includes/external/**/*.hpp"
    "${CMAKE_SOURCE_DIR}/includes/external/glfw/include/**/*.hpp"
    "${CMAKE_SOURCE_DIR}/includes/external/imgui"
)
# add glfw submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/includes/external/glfw)

file(GLOB GLAD_SOURCES "${CMAKE_SOURCE_DIR}/includes/external/glad/*.c")

# Disable pedantic warnings for GLAD on Linux (GLAD casts void* to function pointers)
if(UNIX AND NOT APPLE) # Linux only
    foreach(glad_file ${GLAD_SOURCES})
        set_source_files_properties(${glad_file} PROPERTIES COMPILE_FLAGS "-Wno-pedantic")
    endforeach()
endif()

# Recursively find all source files in src/
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

file(GLOB IMGUI_SOURCES
    "${CMAKE_SOURCE_DIR}/includes/external/imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/includes/external/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/includes/external/imgui/backends/imgui_impl_opengl3.cpp"
)

# Add executable, with APP.cpp as the main entry
add_executable(NUVIO
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${IMGUI_SOURCES}
    ${GLAD_SOURCES}
    ./profiling/Tracy/public/TracyClient.cpp
)

# Include directories
target_include_directories(NUVIO PRIVATE
    ${CMAKE_SOURCE_DIR}/includes/external
    ${CMAKE_SOURCE_DIR}/includes/internal
    ${CMAKE_SOURCE_DIR}/includes/external/glfw/include
    ${CMAKE_SOURCE_DIR}/includes/external/imgui
     ./profiling/Tracy/public
    ./profiling/Tracy/public/tracy

)

target_include_directories(NUVIO PRIVATE
    ./profiling/Tracy/public
    ./profiling/Tracy/public/tracy
)


# Remove -Werror for TracyClient.cpp
set_source_files_properties(
    ./profiling/Tracy/public/TracyClient.cpp
    PROPERTIES COMPILE_FLAGS "-w"
)

target_compile_definitions(NUVIO PRIVATE TRACY_ENABLE)


if(MSVC)
    target_compile_options(NUVIO PRIVATE /W4 /WX)
else()
    target_compile_options(NUVIO PRIVATE -Wall -Wextra )
endif()

add_custom_target(run
    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/NUVIO.exe"
    DEPENDS NUVIO
    WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>"
)

#--post-build--
add_custom_command(
    TARGET NUVIO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:NUVIO>/assets
)
# For shaders:
add_custom_command(
    TARGET NUVIO POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:NUVIO>/shaders
)

target_link_libraries(NUVIO PRIVATE glfw OpenGL::GL)

# set c++ standard
set_target_properties(NUVIO PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
)
