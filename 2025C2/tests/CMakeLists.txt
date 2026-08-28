cmake_minimum_required(VERSION 3.10)
project(MyTests)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_hello test_hello.cpp)
target_link_libraries(test_hello ${GTEST_LIBRARIES} pthread)

add_test(NAME test_hello COMMAND test_hello)