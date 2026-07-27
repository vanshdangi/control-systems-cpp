#include <control_systems/controllers/pid_controller.hpp>
#include <control_systems/plants/point_mass.hpp>
#include <control_systems/utils/csv_logger.hpp>
#include <iomanip>
#include <iostream>

int main() {
    // Constants
    constexpr double mass = 1.0;

    constexpr double target = 10.0;
    constexpr double dt = 0.01;
    constexpr double simulationTime = 30.0;

    // Constructors
    PointMass plant(mass);
    PIDController controller(2.0, 1.0, 2.0);

    // Header
    std::cout << std::left << std::setw(8) << "Time" << std::setw(14) << "Position" << std::setw(14) << "Velocity"
              << std::setw(12) << "Force" << '\n';

    // Main Loop
    for (double t = 0.0; t < simulationTime; t += dt) {
        State state = plant.state();

        double force = controller.update(target, state.position, dt);
        plant.update(force, dt);

        std::cout << std::fixed << std::setprecision(2) << std::setw(8) << t << std::setprecision(6) << std::setw(14)
                  << state.position << std::setw(14) << state.velocity << std::setw(12) << force << '\n';
    }

    return 0;
}