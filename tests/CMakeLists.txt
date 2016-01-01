cmake_minimum_required(VERSION 2.8)

project("ImebraTests")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Wpedantic -pthread --coverage")

file(GLOB imebra_tests_include "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB imebra_tests_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/include)

add_executable(ImebraTests
    ${imebra_tests_include}
    ${imebra_tests_src}
)

find_library(gtest_library NAMES gtest PATHS ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/gtest)
find_library(imebra_library NAMES imebra PATHS ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/imebra ${CMAKE_CURRENT_SOURCE_DIR}/../library-build )

target_link_libraries(ImebraTests ${imebra_library} ${gtest_library} pthread gcov)


