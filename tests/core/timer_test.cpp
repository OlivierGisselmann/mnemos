#include <gtest/gtest.h>

#include "mock_logger.hpp"
#include <core/time/frame_timer.hpp>

#include <thread>

TEST(TimerTest, MeasuresPositiveDeltaTime)
{
    // Init Mock logger
    MockLogger logger;

    // Init timer
    Mnemos::FrameTimerInitInfo info;
    info.limitFramerate = false;
    info.logger = &logger;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 10ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timer.Sleep();

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 9ms and should not exceed a threshold
    EXPECT_GT(delta, 0.009);
    EXPECT_LT(delta, 0.050);
}

TEST(TimerTest, CappedFramerateSleepsCorrectly60)
{
    // Init Mock logger
    MockLogger logger;

    // Init timer
    Mnemos::FrameTimerInitInfo info;
    info.targetFramerate = 60;
    info.limitFramerate = true;
    info.logger = &logger;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    timer.Sleep();

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 15ms and should not exceed 18ms
    EXPECT_GT(delta, 0.015);
    EXPECT_LT(delta, 0.018);
}

TEST(TimerTest, CappedFramerateSleepsCorrectly120)
{
    // Init Mock logger
    MockLogger logger;

    // Init timer
    Mnemos::FrameTimerInitInfo info;
    info.targetFramerate = 120;
    info.limitFramerate = true;
    info.logger = &logger;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    timer.Sleep();

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 7ms and should not exceed 9ms
    EXPECT_GT(delta, 0.007);
    EXPECT_LT(delta, 0.009);
}

TEST(TimerTest, UncappedFramerateMatchesWorkload)
{
    // Init Mock logger
    MockLogger logger;

    // Init timer
    Mnemos::FrameTimerInitInfo info;
    info.limitFramerate = false;
    info.logger = &logger;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    timer.Sleep();

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 7ms and should not exceed 7ms
    EXPECT_GT(delta, 0.004);
    EXPECT_LT(delta, 0.007);
}
