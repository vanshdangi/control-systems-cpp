#include <math/numerical_derivative.hpp>

double NumericalDerivative::update(double input, double dt){
    if(!initialized_){
        previous_ = input;
        initialized_ = true;
        return 0.0;
    }

    derivative_ = (input - previous_)/dt;
    previous_ = input;

    return derivative_;
}

void NumericalDerivative::reset(){
    derivative_ = 0.0;
    previous_ = 0.0;
    initialized_ = false;
}