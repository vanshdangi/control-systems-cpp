#pragma once
#include <control_systems/core/plant.hpp>
#include <control_systems/core/state.hpp>

class PointMass : public Plant {
  public:
    explicit PointMass(double mass = 1.0);
    void update(double force, double dt) override;
    State state() const override;
    void setState(double position, double velocity) override;
    void reset() override;

  private:
    double mass_;
    double position_;
    double velocity_;
};