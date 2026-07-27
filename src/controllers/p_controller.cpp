#include <algorithm>
#include <control_systems/controllers/p_controller.hpp>

PController::PController(double kp, double minOutput, double maxOutput)
    : kp_(kp),
      minOutput_(minOutput),
      maxOutput_(maxOutput) {}

double PController::update(double setpoint, double measurement, [[maybe_unused]] double dt) {
    double unclampedOutput = kp_ * (setpoint - measurement);
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    return output;
}

void PController::reset() {}