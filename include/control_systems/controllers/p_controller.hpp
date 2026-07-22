#pragma once
#include <core/controller.hpp>

class PController : public Controller{
public:
    explicit PController(double kp);

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
};