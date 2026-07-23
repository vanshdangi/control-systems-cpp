#include <iostream>

#include <plants/point_mass.hpp>
#include <plants/spring_mass_damper.hpp>
#include <plants/dc_motor.hpp>
#include <controllers/p_controller.hpp>
#include <controllers/pi_controller.hpp>
#include <controllers/pd_controller.hpp>
#include <controllers/pid_controller.hpp>
#include <corecrt_math_defines.h>

constexpr double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

int main()
{
    //SpringMassDamper plant(1.0, 2.0, 1.0);
    //PointMass plant(1.0);
    constexpr double R  = 2.0;      // Ohm
    constexpr double L  = 0.5;      // Henry

    constexpr double Kt = 0.1;      // N·m/A
    constexpr double Ke = 0.1;      // V/(rad/s)    

    constexpr double J  = 0.02;     // kg·m²
    constexpr double B  = 0.02;     // N·m·s/rad
    DCMotor plant(R, L, Kt, Ke, J, B);
    PIDController controller(2.5, 1.0, 0.55, -12, 12);

    const double target = deg2rad(90.0);
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