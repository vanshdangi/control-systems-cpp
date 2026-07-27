#include <algorithm>
#include <control_systems/controllers/pd_controller.hpp>

PDController::PDController(double kp, double kd, double alpha, double minOutput, double maxOutput)
    : kp_(kp),
      kd_(kd),
      minOutput_(minOutput),
      maxOutput_(maxOutput),
      derivativeFilter_(alpha) {}

double PDController::update(double setpoint, double measurement, double dt) {
    double error = setpoint - measurement;

    // Derivative
    double rawDerivative = derivative_.update(error, dt);
    double filteredDerivative = derivativeFilter_.update(rawDerivative);

    // Output
    double unclampedOutput = kp_ * error + kd_ * filteredDerivative;
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    return output;
}

void PDController::reset() {
    derivative_.reset();
    derivativeFilter_.reset();
}