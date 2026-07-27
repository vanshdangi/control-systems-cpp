#include <control_systems/plants/point_mass.hpp>
#include <gtest/gtest.h>

TEST(PointMass, InitialState) {
    PointMass plant(2.0);

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST(PIDController, PositiveForceAcceleratesForward) {
    PointMass plant(2.0);

    double initialVelocity = plant.state().velocity;
    double initialPosition = plant.state().position;

    plant.update(10.0, 0.01);

    EXPECT_GT(plant.state().velocity, initialVelocity);
    EXPECT_GT(plant.state().position, initialPosition);
}

TEST(PIDController, NegativeForceAcceleratesBackward) {
    PointMass plant(2.0);

    plant.update(-10.0, 0.01);

    EXPECT_LT(plant.state().velocity, 0.0);
    EXPECT_LT(plant.state().position, 0.0);
}

TEST(PointMass, ZeroForceKeepsPlantStationary) {
    PointMass plant(2.0);

    plant.update(0.0, 0.01);

    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
}

TEST(PointMass, ConstantForceProducesExpectedVelocity) {
    PointMass plant(2.0);

    plant.update(10.0, 0.01);

    EXPECT_NEAR(plant.state().velocity, 0.05, 1e-6);
}