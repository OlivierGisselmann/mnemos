#include <gtest/gtest.h>

#include <platform/input/inputsystem.hpp>
#include "../core/mock_logger.hpp"

namespace Mnemos
{
    TEST(InputSystemTest, InitialStateIsEmpty)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        for (int i = 0; i < (int)Key::Count; ++i)
        {
            EXPECT_FALSE(input.IsKeyDown((Key)i));
            EXPECT_FALSE(input.IsKeyPressed((Key)i));
            EXPECT_FALSE(input.IsKeyReleased((Key)i));
        }
    }

    TEST(InputSystemTest, KeyDownUpdatesState)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        input.SetKeyDown(Key::A, true);

        EXPECT_TRUE(input.IsKeyDown(Key::A));
        EXPECT_TRUE(input.IsKeyPressed(Key::A));   // pressed this frame
        EXPECT_FALSE(input.IsKeyReleased(Key::A));
    }

    TEST(InputSystemTest, KeyUpUpdatesState)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        input.SetKeyDown(Key::A, true);
        input.Update();
        input.SetKeyDown(Key::A, false);

        EXPECT_FALSE(input.IsKeyDown(Key::A));
        EXPECT_FALSE(input.IsKeyPressed(Key::A));
        EXPECT_TRUE(input.IsKeyReleased(Key::A));
    }

    TEST(InputSystemTest, MultipleKeysTrackedIndependently)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        input.SetKeyDown(Key::A, true);
        input.SetKeyDown(Key::S, true);
        input.Update();

        EXPECT_TRUE(input.IsKeyDown(Key::A));
        EXPECT_TRUE(input.IsKeyDown(Key::S));

        input.SetKeyDown(Key::A, false);
        input.Update();

        EXPECT_FALSE(input.IsKeyDown(Key::A));
        EXPECT_TRUE(input.IsKeyDown(Key::S));
    }

    TEST(InputSystemTest, MouseButtonStates)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        input.SetMouseButtonDown(MouseButton::Left, true);
        input.Update();

        //EXPECT_TRUE(input.IsMouseButtonDown(MouseButton::Left));
        //EXPECT_TRUE(input.IsMouseButtonPressed(MouseButton::Left));

        input.SetMouseButtonDown(MouseButton::Left, false);
        input.Update();

        //EXPECT_FALSE(input.IsMouseButtonDown(MouseButton::Left));
        //EXPECT_TRUE(input.IsMouseButtonReleased(MouseButton::Left));
    }

    TEST(InputSystemTest, MousePositionTracking)
    {
        MockLogger logger;

        InputSystem input;
        InputSystemInitInfo inputInfo;
        inputInfo.logger = &logger;

        input.Init(inputInfo);

        input.SetMousePosition(100, 200);
        EXPECT_EQ(input.GetMouseX(), 100);
        EXPECT_EQ(input.GetMouseY(), 200);

        input.SetMousePosition(50, 60);
        EXPECT_EQ(input.GetMouseX(), 50);
        EXPECT_EQ(input.GetMouseY(), 60);
    }
}
