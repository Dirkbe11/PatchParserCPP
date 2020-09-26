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
include_directories(..)

set(SOURCES ../PatchParser.hpp UnitTest/PatchParserTest.cpp)
add_executable(PatchParseTest ${SOURCES})

target_compile_features(PatchParseTest PRIVATE cxx_std_17)
target_link_libraries(PatchParseTest gtest gtest_main)
