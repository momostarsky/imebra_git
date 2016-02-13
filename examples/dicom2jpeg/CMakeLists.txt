cmake_minimum_required(VERSION 2.8)

project("dicom2jpeg")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Wpedantic -pthread")

# Specify include and source files
#---------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../library/include)

file(GLOB dicom2jpeg_sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

find_library(imebra_library NAMES imebra libimebra HINTS ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/../imebra ${CMAKE_CURRENT_SOURCE_DIR}/../../library-build )

# Add the source files to the project
#------------------------------------
add_executable(dicom2jpeg ${imebra_sources} ${dicom2jpeg_sources})

target_link_libraries(dicom2jpeg ${imebra_library} pthread)

