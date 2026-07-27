#include <control_systems/filters/low_pass_filter.hpp>

LowPassFilter::LowPassFilter(double alpha) : alpha_(alpha) {}

double LowPassFilter::update(double input) {
    if (!initialized_) {
        previousOutput_ = input;
        initialized_ = true;
        return input;
    }

    previousOutput_ = alpha_ * previousOutput_ + (1.0 - alpha_) * input;

    return previousOutput_;
}

void LowPassFilter::reset() {
    previousOutput_ = 0.0;
    initialized_ = false;
}