#pragma once
#include <core/controller.hpp>
#include <limits>

class PController : public Controller{
public:
    explicit PController(double kp,
                        double minOutput = -std::numeric_limits<double>::infinity(),
                        double maxOutput = std::numeric_limits<double>::infinity()
                    );

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double minOutput_;
    double maxOutput_;
};