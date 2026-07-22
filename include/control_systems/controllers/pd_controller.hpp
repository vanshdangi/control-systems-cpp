#pragma once
#include <core/controller.hpp>
#include <math/numerical_derivative.hpp>

class PDController : public Controller{
public:
    explicit PDController(double kp, double kd);

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double kd_;
    NumericalDerivative derivative_;
};