#include <controllers/pid_controller.hpp>
#include <algorithm>

PIDController::PIDController(double kp,
                            double ki,
                            double kd,
                            double alpha,
                            double minOutput,
                            double maxOutput
                        ): kp_(kp), ki_(ki), kd_(kd), derivativeFilter_(alpha), minOutput_(minOutput), maxOutput_(maxOutput)
{}

// multiplies the constatnt kp_ with the error i.e. (desired position - current position) then adds the integration of error multiplied with constant ki_
double PIDController::update(double setpoint, double measurement, double dt){
    double error = setpoint - measurement;

    // Derivative
    double rawDerivative = derivative_.update(error, dt);
    double filteredDerivative = derivativeFilter_.update(rawDerivative);

    // PID
    double p = kp_ * error;
    double i = ki_ * integrator_.value();
    double d = kd_ * filteredDerivative;
    
    // Output
    double unclampedOutput = p + i + d;
    double output = std::clamp(unclampedOutput, minOutput_, maxOutput_);

    // Update integrator for the NEXT control cycle
    bool atUpperLimit = unclampedOutput >= maxOutput_;
    bool atLowerLimit = unclampedOutput <= minOutput_;

    bool allowIntegration =
        !(atUpperLimit && error > 0) &&
        !(atLowerLimit && error < 0);

    if (allowIntegration){
        integrator_.update(error, dt);
    }

    return output;
}

void PIDController::reset(){
    integrator_.reset();
    derivative_.reset();
    derivativeFilter_.reset();
}