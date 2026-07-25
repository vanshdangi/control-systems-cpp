#include <controllers/p_controller.hpp>
#include <algorithm>

PController::PController(double kp, double minOutput, double maxOutput)
    : kp_(kp), minOutput_(minOutput), maxOutput_(maxOutput)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position)
double PController::update(double setpoint, double measurement, double dt){
    // Output
    double unclampedOutput = kp_ * (setpoint - measurement);
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    return output;
}

void PController::reset(){

}