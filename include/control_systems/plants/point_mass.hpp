#pragma once
#include <core/state.hpp>
#include <core/plant.hpp>

class PointMass : public Plant{
public:
    explicit PointMass(double mass = 1.0);

    void update(double force, double dt) override;
    State state() const override;
    void reset();

private:
    double mass_;
    double position_;
    double velocity_;
};