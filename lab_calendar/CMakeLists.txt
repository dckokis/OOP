cmake_minimum_required(VERSION 3.17)
project(lab_calendar)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Google_Tests/googletest)
include_directories(Google_Tests/googletest/googletest/include)
add_executable(lab_calendar main.cpp date.cpp date.hpp guiCalendar.cpp guiCalendar.hpp rangeCreate.cpp rangeCreate.hpp parser.cpp parser.hpp numberOfDays.hpp numberOfDays.cpp daysCount.cpp daysCount.hpp)
target_link_libraries(lab_calendar gtest gtest_main)