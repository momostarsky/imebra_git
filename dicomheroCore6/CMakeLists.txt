cmake_minimum_required(VERSION 3.1)

set(dicomhero_libraries "")

add_definitions(-DDICOMHERO_CPP_VERSION=${CMAKE_CXX_STANDARD})

# Select the proper charset conversion libraries according to the charset conversion method
#------------------------------------------------------------------------------------------
if("*${DICOMHERO_CHARSET_CONVERSION}*" STREQUAL "*ICONV*")
    message("Using ICONV")
    add_definitions(-DDICOMHERO_USE_ICONV)
    if(APPLE)
        set(dicomhero_libraries ${dicomhero_libraries} iconv)
    endif(APPLE)
elseif("*${DICOMHERO_CHARSET_CONVERSION}*" STREQUAL "*JAVA*")
    message("Using JAVA")
    add_definitions(-DDICOMHERO_USE_JAVA)
elseif("*${IMEBRA_CHARSET_CONVERSION}*" STREQUAL "*WINDOWS*")
    message("Using WINDOWS CHARSET CONVERSION")
    add_definitions(-DDICOMHERO_USE_WINDOWS_CHARSET)
else()
    if(WIN32)
        message("Using WINDOWS CHARSET CONVERSION (default)")
        add_definitions(-DDICOMHERO_USE_WINDOWS_CHARSET)
    else(WIN32)
        message("Using ICONV (default)")
        add_definitions(-DDICOMHERO_USE_ICONV)
        if(APPLE)
            set(dicomhero_libraries ${dicomhero_libraries} iconv)
        endif(APPLE)
    endif(WIN32)
endif()

file(GLOB dicomhero_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/include/dicomhero6/*.h")
file(GLOB imebra_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/include/imebra/*.h")
file(GLOB dicomhero_include "${CMAKE_CURRENT_SOURCE_DIR}/library/src/*.h")
file(GLOB dicomhero_src "${CMAKE_CURRENT_SOURCE_DIR}/library/src/*.cpp")
file(GLOB dicomhero_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.cpp")
file(GLOB dicomhero_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.h")
set(dicomhero_objc_src "")
set(dicomhero_implementation_src_objc "")
set(dicomhero_objc_include "")
set(dicomhero_objc_include_dir "")
set(dicomhero_objc_gnustep_dir "")

if("${DICOMHERO_OBJC}" STREQUAL "1")

    file(GLOB dicomhero_objc_src "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/src/*.*")
    file(GLOB dicomhero_implementation_src_objc "${CMAKE_CURRENT_SOURCE_DIR}/library/implementation/*.mm")
    file(GLOB dicomhero_objc_include "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/include/dicomhero6_objc/*.h")
    add_definitions(-DDICOMHERO_OBJC)

    set(dicomhero_objc_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/include)

    set(objc_compiler_flags "")
    if(APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -framework Foundation -framework CoreServices")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework CoreServices")
        set(objc_compiler_flags "${objc_compiler_flags} -fobjc-arc")
        if(IOS)
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -framework UIKit")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework UIKit")
        else()
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -framework AppKit")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
        endif()
    else()
        set(objc_compiler_flags "${objc_compiler_flags} -fconstant-string-class=NSConstantString")
        set(dicomhero_objc_gnustep_dir "/usr/include/GNUstep")
        set(dicomhero_libraries ${dicomhero_libraries} gnustep-base objc)
    endif()

    if(NOT "${objc_compiler_flags}" STREQUAL "")

        foreach(objcfile ${dicomhero_objc_src})
            set_source_files_properties(${objcfile} PROPERTIES COMPILE_FLAGS ${objc_compiler_flags})
        endforeach(objcfile ${dicomhero_objc_src})

    endif(NOT "${objc_compiler_flags}" STREQUAL "")

endif("${DICOMHERO_OBJC}" STREQUAL "1")


if(NOT "${ADDITIONAL_LIB_PATH}" STREQUAL "")
    link_directories(${LINK_DIRECTORIES} ${ADDITIONAL_LIB_PATH})
endif(NOT "${ADDITIONAL_LIB_PATH}" STREQUAL "")

# Add jpeg2000 if specified
if("${JPEG2000}" STREQUAL "1")
    set(dicomhero_libraries ${dicomhero_libraries} openjpeg)
    add_definitions(-DJPEG2000)
    add_definitions(-DJPEG2000_V1)
    message(STATUS "Adding experimental Jpeg2000 codec (based on OpenJpeg v1.X)")
endif("${JPEG2000}" STREQUAL "1")

if("${JPEG2000}" STREQUAL "2")
    set(dicomhero_libraries ${dicomhero_libraries} openjp2)
    add_definitions(-DJPEG2000)
    add_definitions(-DJPEG2000_V2)
    message(STATUS "Adding experimental Jpeg2000 codec (based on OpenJpeg v2.X)")
endif("${JPEG2000}" STREQUAL "2")

add_library(dicomhero6 ${DICOMHERO_SHARED_STATIC}
    ${dicomhero_implementation_src}
    ${dicomhero_implementation_src_objc}
    ${dicomhero_implementation_include}
    ${dicomhero_objc_src}
    ${dicomhero_objc_include}
    ${dicomhero_include}
    ${dicomhero_src}
    ${imebra_interface}
    ${dicomhero_interface}
)

if(NOT "${ADDITIONAL_INCLUDE_PATH}" STREQUAL "")
    target_include_directories(dicomhero PRIVATE ${ADDITIONAL_INCLUDE_PATH})
endif(NOT "${ADDITIONAL_INCLUDE_PATH}" STREQUAL "")

if("${DICOMHERO_OBJC}" STREQUAL "1")
    set(HIDDEN_FLAGS "")
else("${DICOMHERO_OBJC}" STREQUAL "1")
    set(HIDDEN_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")
endif("${DICOMHERO_OBJC}" STREQUAL "1")

target_include_directories(dicomhero6 PRIVATE ${dicomhero_objc_gnustep_dir})

# Define dependency libraries
#----------------------------
target_link_libraries(dicomhero6 ${dicomhero_libraries} Threads::Threads)

message (STATUS "OBJC INCLUDE:${dicomhero_objc_include_dir}")
message (STATUS "GNU INCLUDE:${dicomhero_objc_gnustep_dir}")

# Define dicomhero public folder
#-------------------------------
target_include_directories(dicomhero6 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/library/include> $<INSTALL_INTERFACE:include>)
target_include_directories(dicomhero6 PUBLIC $<BUILD_INTERFACE:${dicomhero_objc_include_dir}> $<INSTALL_INTERFACE:include>)

set_target_properties(dicomhero6 PROPERTIES VERSION ${DICOMHERO_VERSION}
                                          SOVERSION ${DICOMHERO_MAJOR_VERSION})

if(NOT IOS)

  ##############################################
  #
  # TESTS
  #
  ##############################################

  # Find DCMTK for interoperability tests.
  find_package(DCMTK)
  if(${DCMTK_FOUND})
          message(STATUS "DCMTK found. Interoperability tests enabled")
  else(${DCMTK_FOUND})
          add_definitions(-DDISABLE_DCMTK_INTEROPERABILITY_TEST)
          message(WARNING "WARNING: DCMTK not found. Disabling interoperability tests")
  endif(${DCMTK_FOUND})

  # Enable ExternalProject CMake module (so we can load GoogleTest)
  include(ExternalProject)

  # Download and install GoogleTest
  ExternalProject_Add(
      GTest
      URL https://github.com/google/googletest/archive/release-1.12.1.zip
      CMAKE_ARGS "-Dgtest_force_shared_crt=ON" "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/gtest_install" "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtest_install
  )

  set(dicomhero_tests_objc_src "")
  file(GLOB dicomhero_tests_include "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")
  file(GLOB dicomhero_tests_src "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
  if("${DICOMHERO_OBJC}" STREQUAL "1")

      file(GLOB dicomhero_tests_objc_src "${CMAKE_CURRENT_SOURCE_DIR}/tests/objectivec/*.m*")

      if(NOT "${objc_compiler_flags}" STREQUAL "")

          foreach(objcfile ${dicomhero_tests_objc_src})
              set_source_files_properties(${objcfile} PROPERTIES COMPILE_FLAGS ${objc_compiler_flags})
          endforeach(objcfile ${dicomhero_objc_src})

      endif(NOT "${objc_compiler_flags}" STREQUAL "")

  endif("${DICOMHERO_OBJC}" STREQUAL "1")

  link_directories(${CMAKE_CURRENT_BINARY_DIR}/gtest_install/lib)
  add_executable(dicomheroTests
          ${dicomhero_tests_include}
          ${dicomhero_tests_src}
          ${dicomhero_tests_objc_src}
  )
  add_dependencies(dicomheroTests GTest)
  target_include_directories(dicomheroTests PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gtest_install/include)
  target_link_libraries(dicomheroTests dicomhero6 "gtest")

  if(${DCMTK_FOUND})
      target_link_libraries(dicomheroTests dcmdata dcmimage)
  endif()

  ##############################################
  #
  # RUN TESTS
  #
  ##############################################
  enable_testing()

if(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)
  add_test(RunDicomheroTests dicomheroTests --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles --testLogFile=${CMAKE_CURRENT_BINARY_DIR}/dicomheroTestLogFile.txt)
else()
  add_test(RunDicomheroTests dicomheroTests --corruptedFilesFolder=${CMAKE_CURRENT_SOURCE_DIR}/tests/corruptedfiles)
endif()

endif()


