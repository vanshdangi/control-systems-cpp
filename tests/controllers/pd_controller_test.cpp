#include <control_systems/controllers/pd_controller.hpp>
#include <gtest/gtest.h>

TEST(PDController, ProportionalOutput) {
    PDController controller(2.0, 0.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 4.0);
}

TEST(PDController, PositiveDerivative) {
    PDController controller(0.0, 1.0);

    controller.update(10.0, 9.0, 1.0);
    EXPECT_GT(controller.update(10.0, 8.0, 1.0), 0);
}

TEST(PDController, NegativeDerivative) {
    PDController controller(0.0, 1.0);

    controller.update(10.0, 8.0, 1.0);
    EXPECT_LT(controller.update(10.0, 9.0, 1.0), 0);
}

TEST(PDController, DerivativeZeroForConstantError) {
    PDController controller(0.0, 1.0);

    controller.update(10.0, 8.0, 1.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 0.0);
}

TEST(PDController, ZeroErrorProducesZeroOutput) {
    PDController controller(2.0, 5.0);

    controller.update(10.0, 10.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 10.0, 1.0), 0.0);
}

TEST(PDController, LowPassFilterSmoothsDerivative) {
    PDController controller(0.0, 1.0);
    controller.update(10.0, 10.0, 1.0);

    double spike = controller.update(10.0, 8.0, 1.0);
    double decay1 = controller.update(10.0, 8.0, 1.0);
    double decay2 = controller.update(10.0, 8.0, 1.0);
    double decay3 = controller.update(10.0, 8.0, 1.0);

    EXPECT_GT(spike, decay1);
    EXPECT_GT(decay1, decay2);
    EXPECT_GT(decay2, decay3);
}

TEST(PDController, OutputSaturation) {
    PDController controller(0.0, 1.0, 0.0, -5.0, 5.0);

    controller.update(10.0, 10.0, 1.0);
    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 1.0), 5.0);
}

TEST(PDController, ZeroDeltaTime) {
    PDController controller(5.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 0.0), 10.0);
}