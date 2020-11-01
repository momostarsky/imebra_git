# Options:
# -DDICOMHERO_SHARED_STATIC=SHARED|STATIC (default = SHARED)
# -DJPEG2000=0|1|2 include JPEG2000 codec (1=version 1.X 2=version2.X)
# -DADDITIONAL_INCLUDE_PATH=path to additional include folders (optional)
# -DADDITIONAL_LIB_PATH=path to additional libraries (optional)
# -DDICOMHERO_CHARSET_CONVERSION=ICONV|JAVA|WINDOWS (default = ICONV on posix, WINDOWS on Windows)
# -DDICOMHERO_OBJC=1|0 (default = 0)
# -DIOS=PHONE|SIMULATOR (default not defined)
# -DEMBED_BITCODE=1|0 (default = 0)
# -DCMAKE_OSX_SYSROOT

cmake_minimum_required(VERSION 3.0)

project("dicomhero_imebra")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if("*${CMAKE_BUILD_TYPE}*" STREQUAL "**")
    set(CMAKE_BUILD_TYPE "Debug") # Default build mode is debug
endif()

set(dicomhero_libraries "")

# Select the proper charset conversion libraries according to the charset conversion method
#------------------------------------------------------------------------------------------
if(DICOMHERO_CHARSET_CONVERSION MATCHES ICONV)
    message("Using ICONV")
    add_definitions(-DDICOMHERO_USE_ICONV)
    if(APPLE)
        set(dicomhero_libraries ${dicomhero_libraries} iconv)
    endif(APPLE)
elseif(DICOMHERO_CHARSET_CONVERSION MATCHES JAVA)
    message("Using JAVA")
    add_definitions(-DDICOMHERO_USE_JAVA)
elseif(DICOMHERO_CHARSET_CONVERSION MATCHES WINDOWS)
    message("Using WINDOWS CHARSET CONVERSION")
    add_definitions(-DDICOMHERO_USE_WINDOWS_CHARSET)
else(DICOMHERO_CHARSET_CONVERSION MATCHES ICONV)
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
endif(DICOMHERO_CHARSET_CONVERSION MATCHES ICONV)

# Set the proper logging preprocessor macros
#-------------------------------------------
if(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)
    add_definitions(-DDICOMHERO_LOGGING_LOG4CXX)
    set(dicomhero_libraries ${dicomhero_libraries} log4cxx) # Log4cxx needs additional libraries
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES SYSLOG)
    add_definitions(-DDICOMHERO_LOGGING_SYSLOG)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES COUT)
    add_definitions(-DDICOMHERO_LOGGING_COUT)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES APPLE)
    add_definitions(-DDICOMHERO_LOGGING_APPLE)
elseif(DICOMHERO_LOG_FRAMEWORK MATCHES ANDROID)
    add_definitions(-DDICOMHERO_LOGGING_ANDROID)
endif(DICOMHERO_LOG_FRAMEWORK MATCHES LOG4CXX)

if(DICOMHERO_LOG_LEVEL)
    add_definitions(-DDICOMHERO_LOG_LEVEL_${DICOMHERO_LOG_LEVEL})
endif(DICOMHERO_LOG_LEVEL)


# For IPhone build a static library, otherwise build a dynamic library
#---------------------------------------------------------------------
if(NOT DEFINED DICOMHERO_SHARED_STATIC)
    set(DICOMHERO_SHARED_STATIC "SHARED")
endif(NOT DEFINED DICOMHERO_SHARED_STATIC)

if(APPLE)
    set(DICOMHERO_OBJC 1)
    if(IOS)
        set(DICOMHERO_SHARED_STATIC "STATIC")
        if("${IOS}" MATCHES "PHONE")
            exec_program(xcrun ARGS --sdk iphoneos --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
            set (CMAKE_OSX_ARCHITECTURES armv7 armv7s arm64)
        elseif("${IOS}" MATCHES "SIMULATOR")
            exec_program(xcrun ARGS --sdk iphonesimulator --show-sdk-path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT)
            set (CMAKE_OSX_ARCHITECTURES i386 x86_64)
        else("${IOS}" MATCHES "PHONE")
            message (FATAL_ERROR "Set IOS to PHONE or SIMULATOR")
        endif("${IOS}" MATCHES "PHONE")
        message ("IOS SDK ROOT: ${CMAKE_OSX_SYSROOT}")
    endif(IOS)
endif(APPLE)


##############################################
#
# LIBRARY
#
##############################################
add_definitions(-DDICOMHERO_DLL)
add_definitions(-DDICOMHERO_DLL_EXPORTS)
add_definitions(-DNOMINMAX)

file(GLOB dicomhero_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/include/dicomhero/*.h")
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
    file(GLOB dicomhero_objc_include "${CMAKE_CURRENT_SOURCE_DIR}/wrappers/objectivec/include/dicomhero_objc/*.h")
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
        else(IOS)
            set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -framework AppKit")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework AppKit")
        endif(IOS)
    else(APPLE)
        set(objc_compiler_flags "${objc_compiler_flags} -fconstant-string-class=NSConstantString")
        set(dicomhero_objc_gnustep_dir "/usr/include/GNUstep")
        set(dicomhero_libraries ${dicomhero_libraries} gnustep-base objc)
    endif(APPLE)

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

add_library(dicomhero ${DICOMHERO_SHARED_STATIC}
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


# Add flags specific to the compiler
#-----------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(dicomhero_libraries ${dicomhero_libraries} Kernel32)

else()

    message(STATUS "GNU or Clang detected, adding compile flags")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal ${HIDDEN_FLAGS}")
    set(dicomhero_libraries ${dicomhero_libraries} pthread)
    if("${EMBED_BITCODE}" STREQUAL "1")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode")
    endif("${EMBED_BITCODE}" STREQUAL "1")

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
            message("Debug mode, enabling coverage")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
            set(dicomhero_libraries ${dicomhero_libraries} gcov)
        endif()
    endif()

endif()

target_include_directories(dicomhero PRIVATE ${dicomhero_objc_gnustep_dir})

# Define dependency libraries
#----------------------------
target_link_libraries(dicomhero ${dicomhero_libraries})

message (STATUS "OBJC INCLUDE:${dicomhero_objc_include_dir}")
message (STATUS "GNU INCLUDE:${dicomhero_objc_gnustep_dir}")

# Define dicomhero public folder
#-------------------------------
target_include_directories(dicomhero PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/library/include> $<INSTALL_INTERFACE:include>)
target_include_directories(dicomhero PUBLIC $<BUILD_INTERFACE:${dicomhero_objc_include_dir}> $<INSTALL_INTERFACE:include>)

# Set the library version from DICOMHERO_MAJOR_VERSION, DICOMHERO_MINOR_VERSION,
#  & DICOMHERO_REVISION
#---------------------------------------------------------------------------------
if ("$ENV{DICOMHERO_MAJOR_VERSION}" STREQUAL "")
    set(DICOMHERO_MAJOR_VERSION "5")
else("$ENV{DICOMHERO_MAJOR_VERSION}" STREQUAL "")
    set(DICOMHERO_MAJOR_VERSION "$ENV{DICOMHERO_MAJOR_VERSION}")
endif("$ENV{DICOMHERO_MAJOR_VERSION}" STREQUAL "")

if ("$ENV{DICOMHERO_MINOR_VERSION}" STREQUAL "")
    set(DICOMHERO_MINOR_VERSION "0")
else("$ENV{DICOMHERO_MINOR_VERSION}" STREQUAL "")
    set(DICOMHERO_MINOR_VERSION "$ENV{DICOMHERO_MINOR_VERSION}")
endif("$ENV{DICOMHERO_MINOR_VERSION}" STREQUAL "")

if ("$ENV{DICOMHERO_REVISION}" STREQUAL "")
    set(DICOMHERO_REVISION "0")
else("$ENV{DICOMHERO_REVISION}" STREQUAL "")
    set(DICOMHERO_REVISION "$ENV{DICOMHERO_REVISION}")
endif("$ENV{DICOMHERO_REVISION}" STREQUAL "")

set(DICOMHERO_VERSION "${DICOMHERO_MAJOR_VERSION}.${DICOMHERO_MINOR_VERSION}.${DICOMHERO_REVISION}")

set_target_properties(dicomhero PROPERTIES VERSION ${DICOMHERO_VERSION}
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

    # We need thread support
    find_package(Threads REQUIRED)

    # Enable ExternalProject CMake module (so we can load GoogleTest)
    include(ExternalProject)

    # Download and install GoogleTest
    ExternalProject_Add(
        GTest
        URL https://github.com/google/googletest/archive/release-1.10.0.zip
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

    # GTest always adds "d" to debug build, no matter what's the platform
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        target_link_libraries(dicomheroTests dicomhero "gtestd")
    else()
        target_link_libraries(dicomheroTests dicomhero "gtest")
    endif()

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


    ##############################################
    #
    # DICOM2JPEG example
    #
    ##############################################
    file(GLOB dicom2jpeg_sources "${CMAKE_CURRENT_SOURCE_DIR}/examples/c++/dicom2jpeg/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(dicom2jpeg ${dicom2jpeg_sources})

    target_link_libraries(dicom2jpeg dicomhero)


    ##############################################
    #
    # CHANGETRANSFERSYNTAX example
    #
    ##############################################
    file(GLOB changeTransferSyntax_sources "${CMAKE_CURRENT_SOURCE_DIR}/examples/c++/changeTransferSyntax/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(changeTransferSyntax ${changeTransferSyntax_sources})

    target_link_libraries(changeTransferSyntax dicomhero)


    ##############################################
    #
    # DICOMDIRITEMS example
    #
    ##############################################
    file(GLOB dicomdirItems_sources "${CMAKE_CURRENT_SOURCE_DIR}/examples/c++/dicomdirItems/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(dicomDirItems ${dicomdirItems_sources})

    target_link_libraries(dicomDirItems dicomhero)


    ##############################################
    #
    # scpExample example
    #
    ##############################################
    file(GLOB scpExample_sources "${CMAKE_CURRENT_SOURCE_DIR}/examples/c++/scpExample/*.cpp")

    # Add the source files to the project
    #------------------------------------
    add_executable(scpExample ${scpExample_sources})

    target_link_libraries(scpExample dicomhero)

endif(NOT IOS)


##############################################
#
# PACKAGING
#
##############################################

# Set packaging variables
#------------------------
set(CPACK_PACKAGE_NAME "libdicomhero")
set(CPACK_PACKAGE_CONTACT "paolo@binarno.com")
set(CPACK_PACKAGE_VERSION ${DICOMHERO_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "DICOMHero library for DICOM medical files")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/readme.rst")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://dicomhero.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Paolo Brandoli <paolo@binarno.com>")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

set(CPACK_RPM_PACKAGE_REQUIRES "libc6")

# Generate the control scripts
#-----------------------------
set(SHLIBS_FILE     "${CMAKE_CURRENT_BINARY_DIR}/shlibs")
set(POSTINST_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/postinst")
set(PRERM_SCRIPT    "${CMAKE_CURRENT_BINARY_DIR}/prerm")
set(POSTRM_SCRIPT   "${CMAKE_CURRENT_BINARY_DIR}/postrm")

# Generate postinst, prerm and postrm hooks
file(WRITE "${POSTINST_SCRIPT}" "#!/bin/sh\n\nset -e\n")
file(WRITE "${PRERM_SCRIPT}"    "#!/bin/sh\n\nset -e\n")
file(WRITE "${POSTRM_SCRIPT}"   "#!/bin/sh\n\nset -e\n")

# Generate shlibs
file(WRITE "${SHLIBS_FILE}" "libdicomhero ${DICOMHERO_MAJOR_VERSION} ${CPACK_PACKAGE_NAME}\n")
file(APPEND "${POSTINST_SCRIPT}"
     "if [ \"$1\" = \"configure\" ]; then
        ldconfig
fi
")
file(APPEND "${POSTRM_SCRIPT}"
     "if [ \"$1\" = \"remove\" ]; then
        ldconfig
fi")

execute_process(COMMAND chmod 644 "${SHLIBS_FILE}")
execute_process(COMMAND chmod 755 "${POSTINST_SCRIPT}" "${PRERM_SCRIPT}" "${POSTRM_SCRIPT}")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${SHLIBS_FILE};${POSTINST_SCRIPT};${PRERM_SCRIPT};${POSTRM_SCRIPT}")

# Write license file
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/copyright"
     "Copyright (C) 2020 ${CPACK_DEBIAN_PACKAGE_MAINTAINER}")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/copyright"
        DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/"
        PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ
        WORLD_READ)

install(TARGETS dicomhero EXPORT dicomheroConfig LIBRARY DESTINATION lib
                                                 ARCHIVE DESTINATION lib
                                                 RUNTIME DESTINATION bin
                                                 PUBLIC_HEADER DESTINATION include
                                                 COMPONENT "DICOMHERO Shared library")

install(FILES ${imebra_interface} DESTINATION include/imebra COMPONENT "DICOMHero legacy include files")
install(FILES ${dicomhero_interface} DESTINATION include/dicomhero COMPONENT "DICOMHero include files")

if("${DICOMHERO_OBJC}" STREQUAL "1")
    install(FILES ${dicomhero_objc_include} DESTINATION include/dicomhero_objc COMPONENT "DICOMHero objc include files")
endif("${DICOMHERO_OBJC}" STREQUAL "1")

install(EXPORT dicomheroConfig DESTINATION share/dicomhero/cmake)

include(CPack)
