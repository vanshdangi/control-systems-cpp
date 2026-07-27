#include <control_systems/math/integrator.hpp>

#include <cmath>

double Integrator::update(double input, double dt) {
    if (dt <= 0.0 || !std::isfinite(dt)) {
        return integral_;
    }

    integral_ += input * dt;
    return integral_;
}

double Integrator::value() const {
    return integral_;
}

void Integrator::reset() {
    integral_ = 0.0;
}