
cmake_minimum_required(VERSION 3.10)

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/tools/cmake/CompilerOptions.cmake")

project(vulkan-examples VERSION 0.0.1)

find_package(Vulkan REQUIRED)

add_subdirectory(src/cube)
