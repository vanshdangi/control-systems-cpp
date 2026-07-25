#include <iostream>
#include <iomanip>

#include <plants/spring_mass_damper.hpp>
#include <controllers/pid_controller.hpp>
#include <utils/csv_logger.hpp>

int main()
{
    // Constants
    constexpr double mass           = 1.0;
    constexpr double springK        = 2.0;
    constexpr double damping        = 1.0;

    constexpr double target         = 10.0;
    constexpr double dt             = 0.01;
    constexpr double simulationTime = 30.0;

    // Constructors
    SpringMassDamper plant(mass, springK, damping);
    PIDController controller(2.0, 1.0, 2.0);
    CsvLogger logger("output/pid_spring_mass_damper.csv");

    // Header
    logger.writeHeader({"Time", "Position", "Velocity", "Force"});

    std::cout << std::left
            << std::setw(8)  << "Time"
            << std::setw(14) << "Position"
            << std::setw(14) << "Velocity"
            << std::setw(12) << "Force"
            << '\n';

    // Main Loop
    for (double t = 0.0; t < simulationTime; t += dt)
    {
        State state = plant.state();

        double force = controller.update(target, state.position, dt);
        plant.update(force, dt);

        // Log to CSV
        logger.write(t, state, force);

        std::cout << std::fixed
                << std::setprecision(2)
                << std::setw(8) << t
                << std::setprecision(6)
                << std::setw(14) << state.position
                << std::setw(14) << state.velocity
                << std::setw(12) << force
                << '\n';
    }

    return 0;
}