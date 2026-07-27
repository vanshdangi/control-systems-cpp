#include <control_systems/controllers/p_controller.hpp>
#include <gtest/gtest.h>

TEST(PController, ZeroErrorProducesZeroOutput) {
    PController controller(2.0);

    EXPECT_DOUBLE_EQ(controller.update(5.0, 5.0, 0.01), 0.0);
}

TEST(PController, PositiveError) {
    PController controller(2.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 0.01), 4.0);
}

TEST(PController, NegativeError) {
    PController controller(2.0);

    EXPECT_DOUBLE_EQ(controller.update(8.0, 10.0, 0.01), -4.0);
}

TEST(PController, GainScaling) {
    PController controller(5.0);

    EXPECT_DOUBLE_EQ(controller.update(2.0, 1.0, 0.01), 5.0);
}

TEST(PController, OutputSaturation) {
    PController controller(5.0, -5.0, 5.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 0.01), 5.0);
}