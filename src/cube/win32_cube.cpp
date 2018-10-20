
#include <iostream>

#include <vulkan/vulkan.hpp>

#include <Windows.h>

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    LRESULT result = 0;

    switch (uMsg) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default: {
            result = DefWindowProcA(hwnd, uMsg, wParam, lParam);
            break;
        }
    }

    return result;
}

int CALLBACK WinMain(HINSTANCE hInstance,
                     HINSTANCE /*hPrevInstance*/,
                     LPSTR /*lpCmdLine*/,
                     int /*nCmdShow*/)
{
    const char windowClassName[]   = "VulkanExamplesWindowClass";
    const char windowName[]        = "Vulkan Examples";
    DWORD      windowStyle         = WS_OVERLAPPEDWINDOW;
    DWORD      windowExtendedStyle = 0;
    int        screenWidth         = 1280;
    int        screenHeight        = 720;

    WNDCLASSEXA wce   = {};
    wce.cbSize        = sizeof(WNDCLASSEXA);
    wce.style         = CS_HREDRAW | CS_VREDRAW;
    wce.lpfnWndProc   = WindowProc;
    wce.hInstance     = hInstance;
    wce.lpszClassName = windowClassName;

    if (!RegisterClassExA(&wce)) {
        HRESULT result = HRESULT_FROM_WIN32(GetLastError());
        return result;
    }

    RECT windowRect = {0, 0, screenWidth, screenHeight};

    if (!AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowExtendedStyle)) {
        HRESULT result = HRESULT_FROM_WIN32(GetLastError());
        return result;
    }

    int windowWidth  = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    HWND windowHandle = CreateWindowExA(windowExtendedStyle,
                                        windowClassName,
                                        windowName,
                                        windowStyle | WS_VISIBLE,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        windowWidth,
                                        windowHeight,
                                        NULL,
                                        NULL,
                                        hInstance,
                                        NULL);

    if (!windowHandle) {
        HRESULT result = HRESULT_FROM_WIN32(GetLastError());
        return result;
    }

    // BEGIN Vulkan API
    try {
        vk::ApplicationInfo appInfo = {};
        appInfo.pApplicationName    = windowName;
        appInfo.applicationVersion  = VK_MAKE_VERSION(0, 0, 1);
        appInfo.pEngineName         = "none";
        appInfo.engineVersion       = VK_MAKE_VERSION(0, 0, 1);
        appInfo.apiVersion          = VK_API_VERSION_1_1;

        vk::InstanceCreateInfo createInfo  = {};
        createInfo.pApplicationInfo        = &appInfo;
        createInfo.enabledLayerCount       = 0;
        createInfo.ppEnabledLayerNames     = nullptr;
        createInfo.enabledExtensionCount   = 0;
        createInfo.ppEnabledExtensionNames = nullptr;

        vk::Instance vulkanInstance = vk::createInstance(createInfo);
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // END Vulkan API

    MSG msg = {};

    while (msg.message != WM_QUIT) {
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message != WM_QUIT) {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
    }

    return static_cast<int>(msg.wParam);
}
