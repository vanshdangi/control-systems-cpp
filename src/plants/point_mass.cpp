#include <cmath>
#include <control_systems/plants/point_mass.hpp>

PointMass::PointMass(double mass) : mass_(mass), position_(0.0), velocity_(0.0) {}

void PointMass::update(double force, double dt) {
    if (dt <= 0.0 || !std::isfinite(dt)) {
        return;
    }

    const double acceleration = force / mass_;
    velocity_ += acceleration * dt;
    position_ += velocity_ * dt;
}

State PointMass::state() const {
    return {position_, velocity_};
}

void PointMass::setState(double position, double velocity) {
    position_ = position;
    velocity_ = velocity;
}

void PointMass::reset() {
    position_ = 0.0;
    velocity_ = 0.0;
}