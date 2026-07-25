#include <gtest/gtest.h>
#include <controllers/pi_controller.hpp>

TEST(PIController, IntegralAccumulation){
    PIController controller(0.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 2.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 4.0);
}

TEST(PIController, NegativeIntegralAccumulation)
{
    PIController controller(0.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(0.0, 2.0, 1.0), 0.0);
    EXPECT_DOUBLE_EQ(controller.update(0.0, 2.0, 1.0), -2.0);
    EXPECT_DOUBLE_EQ(controller.update(0.0, 2.0, 1.0), -4.0);
}

TEST(PIController, OutputRemainsSaturated){
    PIController controller(0.0, 10.0, -5.0, 5.0);

    for (int i = 0; i < 100; ++i){
        controller.update(10.0, 0.0, 1.0);
    }

    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 1.0), 5.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 1.0), 5.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 1.0), 5.0);
}


TEST(PIController, ZeroErrorAfterIntegration){
    PIController controller(0.0, 1.0);

    controller.update(10.0, 8.0, 1.0);
    controller.update(10.0, 8.0, 1.0);
    controller.update(10.0, 8.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 10.0, 1.0), 6);
}

TEST(PIController, OutputSaturation){
    PIController controller(5.0, 1.0, -5.0, 5.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 0.01), 5.0);
}

TEST(PIController, ZeroDeltaTime){
    PIController controller(5.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 0.0), 10.0);
}