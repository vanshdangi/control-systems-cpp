#include <controllers/pd_controller.hpp>

PDController::PDController(double kp, double kd)
    : kp_(kp), kd_(kd)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position) then adds the derivative of error multiplied with constant ki_
double PDController::update(double setpoint, const State& state, double dt){
    double error = setpoint - state.position;
    return kp_*error + kd_*derivative_.update(error, dt);
}

void PDController::reset(){
    derivative_.reset();
}