#include <gtest/gtest.h>

#include <platform/platform.hpp>
#include <platform/window/window_win32.hpp>
#include <platform/window/window_linux.hpp>

#include "../core/mock_logger.hpp"

TEST(WindowTest, CreateWindowWithCorrectSize)
{
    MockLogger logger;

    // Window initialization
    Mnemos::WindowInitInfo windowConfig;
    windowConfig.width = 1280;
    windowConfig.height = 720;
    windowConfig.title = "TestWindow";
    windowConfig.fullscreen = false;
    windowConfig.logger = &logger;

    #if defined(MNEMOS_PLATFORM_LINUX)
        Mnemos::LinuxWindow window;
    #elif defined(MNEMOS_PLATFORM_WIN32)
        Mnemos::Win32Window window;
    #endif

    EXPECT_TRUE(window.Init(windowConfig));

    EXPECT_EQ(window.GetWidth(), 1280);
    EXPECT_EQ(window.GetHeight(), 720);

    window.Shutdown();
}

TEST(WindowTest, ShouldCloseDefaultsToFalse)
{
    MockLogger logger;

    // Window initialization
    Mnemos::WindowInitInfo windowConfig;
    windowConfig.width = 800;
    windowConfig.height = 600;
    windowConfig.title = "TestWindow";
    windowConfig.fullscreen = false;
    windowConfig.logger = &logger;

    #if defined(MNEMOS_PLATFORM_LINUX)
        Mnemos::LinuxWindow window;
    #elif defined(MNEMOS_PLATFORM_WIN32)
        Mnemos::Win32Window window;
    #endif

    EXPECT_TRUE(window.Init(windowConfig));

    EXPECT_FALSE(window.CloseRequested());

    window.Shutdown();
}

TEST(WindowTest, CanPollEventsWithoutCrash)
{
    MockLogger logger;
    
    // Window initialization
    Mnemos::WindowInitInfo windowConfig;
    windowConfig.width = 800;
    windowConfig.height = 600;
    windowConfig.title = "TestWindow";
    windowConfig.fullscreen = false;
    windowConfig.logger = &logger;

    #if defined(MNEMOS_PLATFORM_LINUX)
        Mnemos::LinuxWindow window;
    #elif defined(MNEMOS_PLATFORM_WIN32)
        Mnemos::Win32Window window;
    #endif

    EXPECT_TRUE(window.Init(windowConfig));

    window.PollEvents();

    window.Shutdown();
}
