#pragma once
#include <core/controller.hpp>
#include <math/integrator.hpp>
#include <filters/low_pass_filter.hpp>
#include <math/numerical_derivative.hpp>
#include <limits>

class PIDController : public Controller{
public:
    explicit PIDController(double kp,
                        double ki,
                        double kd,
                        double minOutput = -std::numeric_limits<double>::infinity(),
                        double maxOutput = std::numeric_limits<double>::infinity()
                    );

    double update(double setpoint, double measurement, double dt) override;

    void reset() override;

private:
    double kp_;
    double ki_;
    double kd_;
    Integrator integrator_;
    NumericalDerivative derivative_;
    LowPassFilter derivativeFilter_;
    double minOutput_;
    double maxOutput_;
};