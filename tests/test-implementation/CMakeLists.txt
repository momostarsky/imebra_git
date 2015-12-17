cmake_minimum_required(VERSION 2.8)

project("ImebraTests")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Wpedantic -pthread --coverage")

file(GLOB imebra_interface "${CMAKE_CURRENT_SOURCE_DIR}/../../library/include/**/*.h")
file(GLOB imebra_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.h")
file(GLOB imebra_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.cpp")
file(GLOB imebra_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.cpp")
file(GLOB imebra_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.h")
file(GLOB imebra_implementation_tests_include "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB imebra_implementation_tests_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(ImebraTests
    ${imebra_implementation_src}
    ${imebra_implementation_include}
    ${imebra_include}
    ${imebra_src}
    ${imebra_interface}
    ${imebra_implementation_tests_include}
    ${imebra_implementation_tests_src}
)

find_library(gtest_library NAMES gtest PATHS ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/gtest)

target_link_libraries(ImebraTests ${gtest_library} pthread gcov)


