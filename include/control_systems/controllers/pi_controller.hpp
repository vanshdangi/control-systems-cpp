#pragma once
#include <core/controller.hpp>
#include <math/integrator.hpp>

class PIController : public Controller{
public:
    explicit PIController(double kp, double ki);

    double update(double setpoint, const State& state, double dt) override;

    void reset() override;

private:
    double kp_;
    double ki_;
    Integrator integrator_;
};