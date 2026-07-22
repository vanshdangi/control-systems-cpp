#pragma once

class Integrator{
public:
    Integrator() = default;

    double update(double input, double dt);
    double value() const;
    void reset();

private:
    double integral_ = 0.0;
};