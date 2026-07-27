#pragma once
#include <control_systems/core/state.hpp>
#include <fstream>
#include <initializer_list>
#include <string>

class CsvLogger {
  public:
    CsvLogger(const std::string& filename);
    void writeHeader(std::initializer_list<std::string> headers);
    void write(double time, const State& state, double control);

  private:
    std::ofstream file_;
};