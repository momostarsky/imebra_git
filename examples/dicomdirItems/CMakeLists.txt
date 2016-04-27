cmake_minimum_required(VERSION 2.8)

project("dicomdiritems")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Wpedantic -pthread")

# Specify include and source files
#---------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../library/include)

file(GLOB dicomdiritems_sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

find_library(imebra_library NAMES imebra libimebra HINTS ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/../imebra ${CMAKE_CURRENT_SOURCE_DIR}/../../library-build )

# Add the source files to the project
#------------------------------------
add_executable(dicomdiritems ${imebra_sources} ${dicomdiritems_sources})

target_link_libraries(dicomdiritems ${imebra_library} pthread)

