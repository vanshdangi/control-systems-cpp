#pragma once
#include <string>
#include <initializer_list>
#include <core/state.hpp>
#include <fstream>

class CsvLogger {
public:
    CsvLogger(const std::string& filename);

    void writeHeader(std::initializer_list<std::string> headers);
    void write(double time,
                const State& state,
                double control);

private:
    std::ofstream file_;
};