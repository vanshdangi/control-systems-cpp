#pragma once

class Integrator{
public:
    Integrator() = default;

    double update(double input, double dt);
    void reset();

private:
    double integral_ = 0.0;
};