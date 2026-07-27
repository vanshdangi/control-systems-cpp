#pragma once

class LowPassFilter {
  public:
    explicit LowPassFilter(double alpha = 0.9);
    double update(double input);
    void reset();

  private:
    double alpha_;
    double previousOutput_ = 0.0;
    bool initialized_ = false;
};