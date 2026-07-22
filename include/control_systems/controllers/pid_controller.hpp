#pragma once
#include <core/controller.hpp>
#include <math/integrator.hpp>
#include <math/numerical_derivative.hpp>

class PIDController : public Controller{
public:
    explicit PIDController(double kp, double ki, double kd);

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double ki_;
    double kd_;
    Integrator integrator_;
    NumericalDerivative derivative_;
};