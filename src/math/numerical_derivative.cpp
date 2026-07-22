#include <math/numerical_derivative.hpp>
#include <cmath>

double NumericalDerivative::update(double input, double dt){
    if(!initialized_){
        previous_ = input;
        initialized_ = true;
        derivative_ = 0.0;
        return derivative_;
    }

    if (dt <= 0.0 || !std::isfinite(dt)) {
        return derivative_;
    }

    derivative_ = (input - previous_) / dt;
    previous_ = input;

    return derivative_;
}

double NumericalDerivative::value() const{
    return derivative_;
}

void NumericalDerivative::reset(){
    derivative_ = 0.0;
    previous_ = 0.0;
    initialized_ = false;
}