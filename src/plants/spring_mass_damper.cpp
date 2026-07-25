#include <plants/spring_mass_damper.hpp>
#include <cmath>

SpringMassDamper::SpringMassDamper(double mass,
                            double springConstant,
                            double dampingCoefficient)
    : mass_(mass), position_(0.0), velocity_(0.0), k_(springConstant), c_(dampingCoefficient)
{}

// ma = f - cv - kx
// m = mass, a  = acceleration, f = force, c = damping constant, v = velocity, k = spring constant, x = position
void SpringMassDamper::update(double force, double dt){
    if (dt <= 0.0 || !std::isfinite(dt)) {
        return;
    }

    const double springForce = -k_ * position_;
    const double dampingForce = -c_ * velocity_;

    const double acceleration = (force + springForce + dampingForce) / mass_;
    velocity_ += acceleration * dt;
    position_ += velocity_ * dt;

}

State SpringMassDamper::state() const{
    return {position_, velocity_};
}

void SpringMassDamper::setState(double position, double velocity){
    position_ = position;
    velocity_ = velocity;
}

void SpringMassDamper::reset(){
    position_ = 0.0;
    velocity_ = 0.0;
}