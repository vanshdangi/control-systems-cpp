#include <control_systems/utils/csv_logger.hpp>
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

namespace {
constexpr const char* kFilename = "test_logger.csv";
}

TEST(CsvLogger, WritesHeader) {
    {
        CsvLogger logger(kFilename);
        logger.writeHeader({"Time", "Position", "Velocity", "Control"});
    }

    std::ifstream file(kFilename);

    ASSERT_TRUE(file.is_open());

    std::string line;
    ASSERT_TRUE(std::getline(file, line));

    EXPECT_EQ(line, "Time,Position,Velocity,Control");

    std::remove(kFilename);
}

TEST(CsvLogger, WritesSingleRow) {
    {
        CsvLogger logger(kFilename);

        logger.writeHeader({"Time", "Position", "Velocity", "Control"});

        State state{1.5, 2.5};
        logger.write(0.1, state, 3.0);
    }

    std::ifstream file(kFilename);

    ASSERT_TRUE(file.is_open());

    std::string line;

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "Time,Position,Velocity,Control");

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "0.1,1.5,2.5,3");

    std::remove(kFilename);
}

TEST(CsvLogger, WritesMultipleRows) {
    {
        CsvLogger logger(kFilename);

        logger.writeHeader({"Time", "Position", "Velocity", "Control"});

        logger.write(0.0, {0.0, 0.0}, 0.0);
        logger.write(0.1, {1.0, 2.0}, 3.0);
        logger.write(0.2, {2.0, 4.0}, 6.0);
    }

    std::ifstream file(kFilename);

    ASSERT_TRUE(file.is_open());

    std::string line;

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "Time,Position,Velocity,Control");

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "0,0,0,0");

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "0.1,1,2,3");

    ASSERT_TRUE(std::getline(file, line));
    EXPECT_EQ(line, "0.2,2,4,6");

    EXPECT_FALSE(std::getline(file, line));

    std::remove(kFilename);
}

TEST(CsvLogger, WritesEmptyHeader) {
    {
        CsvLogger logger(kFilename);
        logger.writeHeader({});
    }

    std::ifstream file(kFilename);

    ASSERT_TRUE(file.is_open());

    std::string line;
    ASSERT_TRUE(std::getline(file, line));

    EXPECT_TRUE(line.empty());

    std::remove(kFilename);
}