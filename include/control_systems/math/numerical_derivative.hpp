#pragma once

class NumericalDerivative{
public:
    double update(double input, double dt);
    double value() const;
    void reset();

private:
    double derivative_ = 0.0;
    double previous_ = 0.0;
    bool initialized_ = false;
};