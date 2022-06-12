cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(game ${SRC})
target_compile_options(game PRIVATE -std=c++20)
target_include_directories(game PRIVATE src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
target_link_libraries(game glfw)
target_include_directories(game PRIVATE lib/glfw/include)
target_compile_definitions(game PRIVATE GLFW_INCLUDE_NONE)

# add later
# add_subdirectory(lib/glm)
# target_link_libraries(game glm)
# target_include_directories(game PRIVATE lib/glm)

# add_subdirectory(lib/toml)
# target_link_libraries(game tomlplusplus_tomlplusplus)
# target_include_directories(game PRIVATE lib/toml/include)

add_subdirectory(lib/bgfx)
target_link_libraries(game bgfx)
target_include_directories(game PRIVATE lib/bgfx/bgfx/include)
target_include_directories(game PRIVATE lib/bgfx/bx/include)
