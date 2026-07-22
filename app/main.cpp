#include <iostream>

#include <plants/point_mass.hpp>
#include <plants/spring_mass_damper.hpp>
#include <controllers/p_controller.hpp>
#include <controllers/pi_controller.hpp>
#include <controllers/pd_controller.hpp>
#include <controllers/pid_controller.hpp>


int main()
{
    //SpringMassDamper plant(1.0, 2.0, 1.0);
    PointMass plant(1.0);
    PIDController controller(2.0, 1.0, 2.0);

    const double target = 10.0;
    const double dt = 0.01;

    for(double t = 0.0; t < 30.0; t += dt){
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