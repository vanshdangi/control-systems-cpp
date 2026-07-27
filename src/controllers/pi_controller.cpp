#include <algorithm>
#include <control_systems/controllers/pi_controller.hpp>

PIController::PIController(double kp, double ki, double minOutput, double maxOutput)
    : kp_(kp),
      ki_(ki),
      minOutput_(minOutput),
      maxOutput_(maxOutput) {}

double PIController::update(double setpoint, double measurement, double dt) {
    double error = setpoint - measurement;

    // PI
    double p = kp_ * error;
    double i = ki_ * integrator_.value();

    // Output
    double unclampedOutput = p + i;
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    // Update integrator for the NEXT control cycle
    bool atUpperLimit = output >= maxOutput_;
    bool atLowerLimit = output <= minOutput_;
    if (!(atUpperLimit && error > 0) && !(atLowerLimit && error < 0)) {
        integrator_.update(error, dt);
    }

    return output;
}

void PIController::reset() {
    integrator_.reset();
}