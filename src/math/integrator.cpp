#include <math/integrator.hpp>

double Integrator::update(double input, double dt){
    integral_ += input * dt;
    return integral_;
}

void Integrator::reset(){
    integral_ = 0.0;
}