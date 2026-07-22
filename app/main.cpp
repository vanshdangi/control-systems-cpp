#include <iostream>

#include <plants/point_mass.hpp>
#include <controllers/p_controller.hpp>


int main()
{
    PointMass plant;
    PController controller(2.0);

    const double target = 10.0;
    const double dt = 0.01;

    for(double t = 0.0; t < 10.0; t += dt){
        State state = plant.state();
        double force = controller.update(target, state, dt);
        plant.update(force, dt);

        std::cout << t << ", "
              << state.position << ", "
              << state.velocity << ", "
              << force << '\n';
    }
    return 0;
}

/*
control-systems-cpp/
    controllers/
        PController
        PIController
        PDController
        PIDController
        BangBangController
        FeedForwardController
    filters/
        LowPassFilter
        MovingAverage
        ExponentialMovingAverage
    math/
        Integrator
        Differentiator
        NumericalDerivative
    core/
        Controller
        System
        State
        Signal
    logging/
        DataLogger
*/