cmake_minimum_required(VERSION 2.8)

project("dicomherojni")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal")
    set(DICOMHERO_JNILIBRARIES pthread)

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

    message(STATUS "CLANG detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal")
    set(DICOMHEROJNI_LIBRARIES pthread)

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Wp64")
    set(DICOMHEROJNI_LIBRARIES Kernel32)

endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

add_definitions(-DDICOMHERO_USE_JAVA)

find_package(JNI REQUIRED)

set(DICOMHERO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/../../library/include" ${JNI_INCLUDE_DIRS})
set(DICOMHERO_LIBRARIES ${DICOMHERO_LIBRARIES} ${JNI_LIBRARIES})
message("Java libraries: ${JNI_LIBRARIES}")

include_directories(${DICOMHERO_INCLUDE})

file(GLOB dicomhero_interface "${CMAKE_CURRENT_SOURCE_DIR}/../../library/include/**/*.h")
file(GLOB dicomhero_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.h")
file(GLOB dicomhero_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/src/*.cpp")
file(GLOB dicomhero_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.cpp")
file(GLOB dicomhero_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/../../library/implementation/*.h")
file(GLOB dicomhero_swig_implementation "${CMAKE_CURRENT_SOURCE_DIR}/java_wrapper.cxx")

add_library(dicomherojni SHARED
    ${dicomhero_implementation_src}
    ${dicomhero_implementation_include}
    ${dicomhero_include}
    ${dicomhero_src}
    ${dicomhero_interface}
    ${dicomhero_swig_implementation}
)

target_link_libraries(dicomherojni ${DICOMHERO_LIBRARIES})

