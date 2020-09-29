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
include_directories(../patch_parser_cpp)
set(SOURCES ../patch_parser_cpp/patch_parser.hpp UnitTest/PatchParserTest.cpp)
add_executable(PatchParseTest ${SOURCES})
target_link_libraries(PatchParseTest gtest gtest_main)
