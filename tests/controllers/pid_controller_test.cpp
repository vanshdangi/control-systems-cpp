#include <control_systems/controllers/pid_controller.hpp>
#include <gtest/gtest.h>

TEST(PIDController, CombinedPIDOutput) {
    PIDController controller(2.0, 1.0, 3.0);

    // First sample
    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 4.0);

    // Second sample (same error)
    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 1.0), 6.0);
}

TEST(PIDController, IntegralPersistsAfterZeroError) {
    PIDController controller(0.0, 1.0, 0.0);

    controller.update(10.0, 8.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 10.0, 1.0), 2.0);
}

TEST(PIDController, LowPassFilterSmoothsDerivative) {
    PIDController controller(0.0, 0.0, 1.0);

    controller.update(10.0, 10.0, 1.0);

    double spike = controller.update(10.0, 8.0, 1.0);
    double decay1 = controller.update(10.0, 8.0, 1.0);
    double decay2 = controller.update(10.0, 8.0, 1.0);
    double decay3 = controller.update(10.0, 8.0, 1.0);

    EXPECT_GT(spike, decay1);
    EXPECT_GT(decay1, decay2);
    EXPECT_GT(decay2, decay3);
}

TEST(PIDController, OutputSaturation) {
    PIDController controller(100.0, 100.0, 100.0, 0.0, -5.0, 5.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 0.0, 1.0), 5.0);
}

TEST(PIDController, ZeroDeltaTime) {
    PIDController controller(5.0, 1.0, 1.0);

    EXPECT_DOUBLE_EQ(controller.update(10.0, 8.0, 0.0), 10.0);
}