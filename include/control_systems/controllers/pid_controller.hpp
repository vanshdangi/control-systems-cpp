#pragma once
#include <control_systems/core/controller.hpp>
#include <control_systems/filters/low_pass_filter.hpp>
#include <control_systems/math/integrator.hpp>
#include <control_systems/math/numerical_derivative.hpp>
#include <limits>

class PIDController : public Controller {
  public:
    explicit PIDController(double kp,
                           double ki,
                           double kd,
                           double alpha = 0.9,
                           double minOutput = -std::numeric_limits<double>::infinity(),
                           double maxOutput = std::numeric_limits<double>::infinity());
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