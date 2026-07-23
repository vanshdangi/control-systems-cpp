#include <plants/dc_motor.hpp>
#include <cassert>

DCMotor::DCMotor(
            double resistance,
            double inductance,
            double torqueConstant,
            double backEmfConstant,
            double inertia,
            double friction
        ) : resistance_(resistance), inductance_(inductance), torqueConstant_(torqueConstant), backEmfConstant_(backEmfConstant), inertia_(inertia), friction_(friction){
    assert(inductance > 0.0);
    assert(inertia > 0.0);
    assert(resistance >= 0.0);
    assert(friction >= 0.0);
}


void DCMotor::update(double voltage, double dt){
    double backEMF = backEmfConstant_ * velocity_;

    double currentDerivative = (voltage - resistance_*current_ - backEMF)/inductance_;
    current_ = currentIntegrator_.update(currentDerivative, dt);

    double motorTorque = torqueConstant_ * current_;

    double angularAcceleration = (motorTorque - friction_*velocity_ - loadTorque_)/inertia_;

    velocity_ = velocityIntegrator_.update(angularAcceleration, dt);
    position_ = positionIntegrator_.update(velocity_, dt);
}

void DCMotor::setLoadTorque(double torque){
    loadTorque_ = torque;
}

State DCMotor::state() const{
    return {position_, velocity_};
}

void DCMotor::reset(){
    velocity_ = 0.0;
    position_ = 0.0;
    current_ = 0.0;
    loadTorque_ = 0.0;
}