#include <controllers/pid_controller.hpp>

PIDController::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position) then adds the integration of error multiplied with constant ki_
double PIDController::update(double setpoint, const State& state, double dt){
    double error = setpoint - state.position;
    return kp_ * error + 
        ki_ * integrator_.update(error, dt) +
        kd_ * derivative_.update(error, dt);
}

void PIDController::reset(){
    integrator_.reset();
    derivative_.reset();
}