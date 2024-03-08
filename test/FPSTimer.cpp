#include "../src/FPSTimer.h"
#include <gtest/gtest.h>

float tolerance = 0.003f;

TEST(FPSTimer, fpsTimer)
{
    FPSTimer instance;

    for(int i = 0; i < 100; i++)
    {
        instance.clamp_fps(i);
        float delta = instance.get_delta();

        EXPECT_TRUE(std::abs(delta - 0.016f) < tolerance);
    }


}