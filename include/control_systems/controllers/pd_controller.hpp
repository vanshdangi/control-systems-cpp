#pragma once
#include <control_systems/core/controller.hpp>
#include <control_systems/filters/low_pass_filter.hpp>
#include <control_systems/math/numerical_derivative.hpp>
#include <limits>

class PDController : public Controller {
  public:
    explicit PDController(double kp,
                          double kd,
                          double alpha = 0.9,
                          double minOutput = -std::numeric_limits<double>::infinity(),
                          double maxOutput = std::numeric_limits<double>::infinity());
    double update(double setpoint, double measurement, double dt) override;
    void reset() override;

  private:
    double kp_;
    double kd_;
    NumericalDerivative derivative_;
    double minOutput_;
    double maxOutput_;
    LowPassFilter derivativeFilter_;
};