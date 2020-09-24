cmake_minimum_required(VERSION 3.10)
project(PatchParserTest)

set(CMAKE_CXX_STANDARD 17)

###############
#Add GoogleTest
###############
add_subdirectory(googletest)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

###############
#Build test executable
###############
add_executable(PatchParseTest ../PatchParser.hpp UnitTest/PatchParse1.cpp)
target_link_libraries(PatchParseTest gtest gtest_main)
