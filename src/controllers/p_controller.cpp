#include <controllers/p_controller.hpp>

PController::PController(double kp)
    : kp_(kp)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position)
double PController::update(double setpoint, const State& state, double dt){
    return kp_ * (setpoint - state.position);
}

void PController::reset(){

}