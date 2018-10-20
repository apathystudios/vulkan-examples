
add_executable(cube)

target_link_libraries(cube PRIVATE Vulkan::Vulkan)
target_compile_features(cube PRIVATE cxx_std_20)

if (WIN32)
    target_sources(cube PRIVATE win32_cube.cpp)
    set_target_properties(cube PROPERTIES WIN32_EXECUTABLE ON)
    target_compile_definitions(cube PRIVATE VK_USE_PLATFORM_WIN32_KHR)
    target_compile_options(cube PRIVATE "-W4" "-WX" "-GR-" "-permissive-")
    target_link_libraries(cube PRIVATE "User32.lib")
endif()
