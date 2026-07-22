#include <controllers/pi_controller.hpp>

PIController::PIController(double kp, double ki)
    : kp_(kp), ki_(ki)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position) then adds the integration of error multiplied with constant ki_
double PIController::update(double setpoint, const State& state, double dt){
    double error = setpoint - state.position;
    return kp_*error + ki_*integrator_.update(error, dt);
}

void PIController::reset(){
    integrator_.reset();
}