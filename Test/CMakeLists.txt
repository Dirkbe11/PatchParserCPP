cmake_minimum_required(VERSION 3.10)
project(PatchParserTest)

set(CMAKE_CXX_STANDARD 17)

###############
#Add GoogleTest
###############
add_subdirectory(googletest)

###############
#Build test executable
###############
include_directories(../include)
set(SOURCES ../include/PatchParserCPP/PatchParser.hpp UnitTest/PatchParserTest.cpp)
add_executable(PatchParseTest ${SOURCES})
target_link_libraries(PatchParseTest gtest gtest_main)
