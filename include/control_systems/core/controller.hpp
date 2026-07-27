#pragma once
#include <control_systems/core/plant.hpp>
#include <control_systems/core/state.hpp>

class Controller {
  public:
    virtual double update(double setpoint, double measurement, double dt) = 0;
    virtual void reset() = 0;
    virtual ~Controller() = default;
};