#pragma once
#include <core/controller.hpp>
#include <math/integrator.hpp>
#include <limits>

class PIController : public Controller{
public:
    explicit PIController(double kp,
                        double ki,
                        double minOutput = -std::numeric_limits<double>::infinity(),
                        double maxOutput = std::numeric_limits<double>::infinity()
                    );

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double ki_;
    Integrator integrator_;
    double minOutput_;
    double maxOutput_;
};