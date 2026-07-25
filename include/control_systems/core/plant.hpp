#pragma once
#include <core/state.hpp>

class Plant{
public:
    virtual void update(double input, double dt) = 0;

    virtual State state() const = 0;

    virtual void setState(double position, double velocity) = 0;

    virtual void reset() = 0;

    virtual ~Plant() = default;
};