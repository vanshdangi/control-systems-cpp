#pragma once
#include <core/state.hpp>
#include <core/plant.hpp>
#include <math/integrator.hpp>

class DCMotor : public Plant{
public:
    explicit DCMotor(
            double resistance,
            double inductance,
            double torqueConstant,
            double backEmfConstant,
            double inertia,
            double friction
        );

    void update(double voltage, double dt) override;
    void setLoadTorque(double torque);
    State state() const override;
    void setState(double position, double velocity) override;
    void setState(double position, double velocity, double current);
    void reset() override;

private:
    double velocity_;
    double position_;
    double current_;
    double loadTorque_ = 0.0;
    Integrator currentIntegrator_;
    Integrator velocityIntegrator_;
    Integrator positionIntegrator_;
    double resistance_;
    double inductance_;
    double torqueConstant_;
    double backEmfConstant_;
    double inertia_;
    double friction_;
};