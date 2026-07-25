#pragma once
#include <core/state.hpp>
#include <core/plant.hpp>

class Controller{
public:
    virtual double update(double setpoint, double measurement, double dt) = 0;

    virtual void reset() = 0;

    virtual ~Controller() = default;
};