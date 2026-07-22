#include <plants/point_mass.hpp>

PointMass::PointMass(double mass)
    : mass_(mass), position_(0.0), velocity_(0.0)
{}

// Applies the force and calculates new position and velocity
void PointMass::update(double force, double dt){
        double acceleration = force / mass_;

        velocity_ += acceleration * dt;
        position_ += velocity_ * dt;
    }

State PointMass::state() const{
    return {position_, velocity_};
}

void PointMass::reset(){
    position_ = 0.0;
    velocity_ = 0.0;
}