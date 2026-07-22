#include <controllers/pi_controller.hpp>
#include <algorithm>

PIController::PIController(double kp, double ki, double minOutput, double maxOutput)
    : kp_(kp), ki_(ki), minOutput_(minOutput), maxOutput_(maxOutput)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position) then adds the integration of error multiplied with constant ki_
double PIController::update(double setpoint, const State& state, double dt){
    double error = setpoint - state.position;

    // PI
    double p = kp_ * error;
    double i = ki_ * integrator_.value();

    // Output
    double unclampedOutput = p + i;
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    // Update integrator for the NEXT control cycle
    bool atUpperLimit = output >= maxOutput_;
    bool atLowerLimit = output <= minOutput_;

    bool allowIntegration =
        !(atUpperLimit && error > 0) &&
        !(atLowerLimit && error < 0);

    if (allowIntegration){
        integrator_.update(error, dt);
    }
    
    return output;
}

void PIController::reset(){
    integrator_.reset();
}