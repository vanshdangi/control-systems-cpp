#pragma once
#include <core/state.hpp>
#include <core/plant.hpp>

class SpringMassDamper : public Plant{
public:
    explicit SpringMassDamper(double mass = 1.0,
                            double springConstant = 2.0,
                            double dampingCoefficient = 1.0);

    void update(double force, double dt) override;
    State state() const override;
    void reset();

private:
    double mass_;
    double position_;
    double velocity_;
    double k_;
    double c_;
};