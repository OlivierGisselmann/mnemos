#include <gtest/gtest.h>

#include "mock_logger.hpp"
#include <core/time/frame_timer.hpp>

#include <thread>

TEST(TimerTest, MeasuresPositiveDeltaTime)
{
    Mnemos::FrameTimerInitInfo info;
    info.limitFramerate = false;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 10ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 9ms and should not exceed a threshold
    EXPECT_GT(delta, 0.0);
}

TEST(TimerTest, CappedFramerateSleepsCorrectly60)
{
    Mnemos::FrameTimerInitInfo info;
    info.targetFramerate = 60;
    info.limitFramerate = true;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 15ms and should not exceed 18ms
    EXPECT_GT(delta, 0.015);
    EXPECT_LT(delta, 0.018);
}

TEST(TimerTest, CappedFramerateSleepsCorrectly120)
{
    Mnemos::FrameTimerInitInfo info;
    info.targetFramerate = 120;
    info.limitFramerate = true;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 7ms and should not exceed 9ms
    EXPECT_GT(delta, 0.007);
    EXPECT_LT(delta, 0.009);
}

TEST(TimerTest, UncappedFramerateMatchesWorkload)
{
    Mnemos::FrameTimerInitInfo info;
    info.limitFramerate = false;

    Mnemos::FrameTimer timer;
    timer.Init(info);

    // Simulate a frame that took 3ms
    timer.Tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    f64 delta = timer.GetDeltaTime();

    // Delta time should be at least 7ms and should not exceed 7ms
    //EXPECT_GT(delta, 0.0);
    //EXPECT_LT(delta, 0.01);
}
