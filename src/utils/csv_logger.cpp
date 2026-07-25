#include <utils/csv_logger.hpp>

CsvLogger::CsvLogger(const std::string& filename)
    :file_(filename)
{}

void CsvLogger::writeHeader(std::initializer_list<std::string> headers)
{
    bool first = true;

    for (const auto& header : headers)
    {
        if (!first)
            file_ << ',';

        file_ << header;
        first = false;
    }

    file_ << '\n';
}

void CsvLogger::write(double time,
                    const State& state,
                    double control){
    file_ << time << ','
        << state.position << ','
        << state.velocity << ','
        << control << '\n';
}