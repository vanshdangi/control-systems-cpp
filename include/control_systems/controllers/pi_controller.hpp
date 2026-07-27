#pragma once
#include <control_systems/core/controller.hpp>
#include <control_systems/math/integrator.hpp>
#include <limits>

class PIController : public Controller {
  public:
    explicit PIController(double kp,
                          double ki,
                          double minOutput = -std::numeric_limits<double>::infinity(),
                          double maxOutput = std::numeric_limits<double>::infinity());
    double update(double setpoint, double measurement, double dt) override;
    void reset() override;

  private:
    double kp_;
    double ki_;
    Integrator integrator_;
    double minOutput_;
    double maxOutput_;
};