#include <control_systems/plants/dc_motor.hpp>
#include <gtest/gtest.h>

class DCMotorTest : public ::testing::Test {
  protected:
    DCMotor plant{
        1.0,  // Resistance (Ω)
        0.5,  // Inductance (H)
        0.1,  // Torque constant (Nm/A)
        0.1,  // Back EMF constant (V/(rad/s))
        0.01, // Inertia (kg·m²)
        0.01  // Friction (N·m·s/rad)
    };
};

TEST_F(DCMotorTest, InitialState) {
    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST_F(DCMotorTest, ZeroVoltageKeepsMotorStationary) {
    plant.update(0.0, 0.01);

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST_F(DCMotorTest, PositiveVoltageAcceleratesForward) {
    plant.update(12.0, 0.01);

    EXPECT_GT(plant.state().position, 0.0);
    EXPECT_GT(plant.state().velocity, 0.0);
}

TEST_F(DCMotorTest, NegativeVoltageAcceleratesBackward) {
    plant.update(-12.0, 0.01);

    EXPECT_LT(plant.state().position, 0.0);
    EXPECT_LT(plant.state().velocity, 0.0);
}

TEST_F(DCMotorTest, PositiveVelocityDecaysWithoutInput) {
    plant.setState(0.0, 10.0, 0.0);

    plant.update(0.0, 0.01);

    EXPECT_LT(plant.state().velocity, 10.0);
}

TEST_F(DCMotorTest, NegativeVelocityDecaysWithoutInput) {
    plant.setState(0.0, -10.0, 0.0);

    plant.update(0.0, 0.01);

    EXPECT_GT(plant.state().velocity, -10.0);
}

TEST_F(DCMotorTest, PositionIntegratesVelocity) {
    for (double t = 0.0; t < 5.0; t += 0.01) {
        plant.update(12.0, 0.01);
    }

    EXPECT_GT(plant.state().velocity, 0.0);
    EXPECT_GT(plant.state().position, 0.0);
}

TEST_F(DCMotorTest, ConstantVoltageReachesSteadySpeed) {
    for (double t = 0.0; t < 20.0; t += 0.01) {
        plant.update(12.0, 0.01);
    }

    double velocity1 = plant.state().velocity;

    for (double t = 0.0; t < 5.0; t += 0.01) {
        plant.update(12.0, 0.01);
    }

    double velocity2 = plant.state().velocity;

    EXPECT_NEAR(velocity1, velocity2, 1e-2);
}

TEST_F(DCMotorTest, VelocityDecaysAfterPowerRemoval) {
    for (double t = 0.0; t < 10.0; t += 0.01) {
        plant.update(12.0, 0.01);
    }

    double poweredVelocity = plant.state().velocity;

    for (double t = 0.0; t < 10.0; t += 0.01) {
        plant.update(0.0, 0.01);
    }

    EXPECT_LT(plant.state().velocity, poweredVelocity);
    EXPECT_NEAR(plant.state().velocity, 0.0, 1e-2);
}

TEST_F(DCMotorTest, ResetClearsState) {
    for (double t = 0.0; t < 2.0; t += 0.01) {
        plant.update(12.0, 0.01);
    }

    plant.setLoadTorque(0.5);
    plant.reset();

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);

    plant.update(0.0, 0.01);

    EXPECT_DOUBLE_EQ(plant.state().position, 0.0);
    EXPECT_DOUBLE_EQ(plant.state().velocity, 0.0);
}

TEST(DCMotor, HigherVoltageProducesHigherSteadySpeed) {
    DCMotor motor6(1.0, 0.5, 0.1, 0.1, 0.01, 0.01);
    DCMotor motor12(1.0, 0.5, 0.1, 0.1, 0.01, 0.01);

    for (double t = 0.0; t < 20.0; t += 0.01) {
        motor6.update(6.0, 0.01);
        motor12.update(12.0, 0.01);
    }

    EXPECT_GT(motor12.state().velocity, motor6.state().velocity);
}

TEST(DCMotor, LoadTorqueReducesSteadySpeed) {
    DCMotor unloaded(1.0, 0.5, 0.1, 0.1, 0.01, 0.01);
    DCMotor loaded(1.0, 0.5, 0.1, 0.1, 0.01, 0.01);

    loaded.setLoadTorque(0.5);

    for (double t = 0.0; t < 20.0; t += 0.01) {
        unloaded.update(12.0, 0.01);
        loaded.update(12.0, 0.01);
    }

    EXPECT_GT(unloaded.state().velocity, loaded.state().velocity);
}