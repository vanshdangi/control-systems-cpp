#pragma once
#include <core/state.hpp>
#include <core/plant.hpp>

class Controller{
public:
    virtual double update(double setpoint, const State& state, double dt) = 0;

    virtual void reset() = 0;

    virtual ~Controller() = default;
};