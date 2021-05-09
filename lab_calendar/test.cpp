#include "parser.hpp"
#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(INPUT, RANGES) {
    ifstream input("testRanges.txt");
    vector<string> testInput = streamReader(input);

    ASSERT_TRUE("range 1 2021 12 2022 | horiz year_once" == testInput[0]);

    Range testRange = CreateRange(testInput);
    Range controlRange{};
    controlRange.dateBegin = Date(1, 1, 2021);
    controlRange.dateEnd = Date(31, 12, 2022);
    controlRange.type = RangeType::RANGE;
    controlRange.orient = false;
    controlRange.yearOnce = true;
    controlRange.yearEveryMonth = false;
    ASSERT_TRUE(testRange.type == controlRange.type);
    ASSERT_TRUE(testRange.orient == controlRange.orient);
    ASSERT_TRUE(testRange.dateEnd == controlRange.dateEnd);
    ASSERT_TRUE(testRange.dateBegin == controlRange.dateBegin);
    ASSERT_TRUE(testRange.yearOnce == controlRange.yearOnce);
    ASSERT_TRUE(testRange.yearEveryMonth == controlRange.yearEveryMonth);
}

