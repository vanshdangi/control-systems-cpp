#include <control_systems/controllers/pid_controller.hpp>
#include <control_systems/plants/dc_motor.hpp>
#include <control_systems/utils/csv_logger.hpp>
#include <corecrt_math_defines.h>
#include <iomanip>
#include <iostream>

constexpr double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

int main() {
    // Constants
    constexpr double R = 2.0;  // Ohm
    constexpr double L = 0.5;  // Henry
    constexpr double Kt = 0.1; // N·m/A
    constexpr double Ke = 0.1; // V/(rad/s)
    constexpr double J = 0.02; // kg·m²
    constexpr double B = 0.02; // N·m·s/rad

    constexpr double target = deg2rad(180.0);
    constexpr double dt = 0.01;
    constexpr double simulationTime = 30.0;

    // Constructors
    DCMotor plant(R, L, Kt, Ke, J, B);
    PIDController controller(2.5, 1.0, 0.55, -12.0, 12.0);
    CsvLogger logger("output/pid_dc_motor_position.csv");

    // Header
    logger.writeHeader({"Time", "Velocity", "Position", "Voltage"});

    std::cout << std::left << std::setw(8) << "Time" << std::setw(14) << "Velocity" << std::setw(14) << "Position"
              << std::setw(12) << "Voltage" << '\n';

    // Main Loop
    for (double t = 0.0; t < simulationTime; t += dt) {
        State state = plant.state();

        double voltage = controller.update(target, state.velocity, dt);
        plant.update(voltage, dt);

        // Log to CSV
        logger.write(t, state, voltage);

        std::cout << std::fixed << std::setprecision(2) << std::setw(8) << t << std::setprecision(6) << std::setw(14)
                  << state.position << std::setw(14) << state.velocity << std::setw(12) << voltage << '\n';
    }

    return 0;
}