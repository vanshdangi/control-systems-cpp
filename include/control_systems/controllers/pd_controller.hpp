#pragma once
#include <core/controller.hpp>
#include <math/numerical_derivative.hpp>
#include <filters/low_pass_filter.hpp>
#include <limits>

class PDController : public Controller{
public:
    explicit PDController(double kp,
                        double kd,
                        double minOutput = -std::numeric_limits<double>::infinity(),
                        double maxOutput = std::numeric_limits<double>::infinity()
                    );

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double kd_;
    NumericalDerivative derivative_;
    double minOutput_;
    double maxOutput_;
    LowPassFilter derivativeFilter_;
};