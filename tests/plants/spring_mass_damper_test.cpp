#include <control_systems/plants/spring_mass_damper.hpp>
#include <gtest/gtest.h>

TEST(SpringMassDamper, InitialState) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST(SpringMassDamper, PositiveForceAcceleratesForward) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    plant.update(10.0, 0.01);

    EXPECT_GT(plant.state().velocity, 0.0);
    EXPECT_GT(plant.state().position, 0.0);
}

TEST(SpringMassDamper, NegativeForceAcceleratesBackward) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    plant.update(-10.0, 0.01);

    EXPECT_LT(plant.state().velocity, 0.0);
    EXPECT_LT(plant.state().position, 0.0);
}

TEST(SpringMassDamper, ZeroInputMaintainsEquilibrium) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    plant.update(0.0, 0.01);

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST(SpringMassDamper, SpringRestoresPositiveDisplacement) {
    SpringMassDamper plant(1.0, 2.0, 0.0);

    plant.setState(1.0, 0.0);

    plant.update(0.0, 0.01);

    EXPECT_LT(plant.state().velocity, 0.0);
}

TEST(SpringMassDamper, SpringRestoresNegativeDisplacement) {
    SpringMassDamper plant(1.0, 2.0, 0.0);

    plant.setState(-1.0, 0.0);

    plant.update(0.0, 0.01);

    EXPECT_GT(plant.state().velocity, 0.0);
}

TEST(SpringMassDamper, DampingOpposesPositiveVelocity) {
    SpringMassDamper plant(1.0, 0.0, 2.0);

    plant.setState(0.0, 5.0);

    plant.update(0.0, 0.01);

    EXPECT_LT(plant.state().velocity, 5.0);
}

TEST(SpringMassDamper, DampingOpposesNegativeVelocity) {
    SpringMassDamper plant(1.0, 0.0, 2.0);

    plant.setState(0.0, -5.0);

    plant.update(0.0, 0.01);

    EXPECT_GT(plant.state().velocity, -5.0);
}

TEST(SpringMassDamper, ReturnsToEquilibrium) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    plant.setState(5.0, 0.0);

    for (double t = 0.0; t < 20.0; t += 0.01) {
        plant.update(0.0, 0.01);
    }

    EXPECT_NEAR(plant.state().position, 0.0, 1e-2);
    EXPECT_NEAR(plant.state().velocity, 0.0, 1e-2);
}

TEST(SpringMassDamper, ConstantForceReachesCorrectEquilibrium) {
    SpringMassDamper plant(1.0, 2.0, 1.0);

    for (double t = 0.0; t < 30.0; t += 0.01) {
        plant.update(10.0, 0.01);
    }

    EXPECT_NEAR(plant.state().position, 5.0, 1e-2);
    EXPECT_NEAR(plant.state().velocity, 0.0, 1e-2);
}