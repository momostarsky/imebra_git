# Options:
# -DDICOMHERO_SHARED_STATIC=SHARED|STATIC (default = SHARED)
# -DJPEG2000=0|1|2 include JPEG2000 codec (1=version 1.X 2=version2.X)
# -DADDITIONAL_INCLUDE_PATH=path to additional include folders (optional)
# -DADDITIONAL_LIB_PATH=path to additional libraries (optional)
# -DDICOMHERO_CHARSET_CONVERSION=ICONV|JAVA|WINDOWS (default = ICONV on posix, WINDOWS on Windows)
# -DDICOMHERO_OBJC=1|0 (default = 0)
# -DEMBED_BITCODE=1|0 (default = 0)

cmake_minimum_required(VERSION 3.0)

project("dicomhero6")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if("*${CMAKE_BUILD_TYPE}*" STREQUAL "**")
    set(CMAKE_BUILD_TYPE "Debug") # Default build mode is debug
endif()

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

if(NOT DEFINED DICOMHERO_SHARED_STATIC)
    set(DICOMHERO_SHARED_STATIC "SHARED")
endif(NOT DEFINED DICOMHERO_SHARED_STATIC)

if(APPLE)
    set(DICOMHERO_OBJC 1)
endif(APPLE)

##############################################
#
# LIBRARY
#
##############################################
add_definitions(-DDICOMHERO_DLL)
add_definitions(-DDICOMHERO_DLL_EXPORTS)
add_definitions(-DNOMINMAX)

# Add flags specific to the compiler
#-----------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message(STATUS "MSVC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /bigobj")
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

# Set the library version from DICOMHERO_MAJOR_VERSION, DICOMHERO_MINOR_VERSION,
#  & DICOMHERO_REVISION
#---------------------------------------------------------------------------------
if ("$ENV{DICOMHERO_MAJOR_VERSION}" STREQUAL "")
    set(DICOMHERO_MAJOR_VERSION "6")
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

# We need thread support
find_package(Threads REQUIRED)

add_subdirectory(dicomheroCore6)

if(NOT IOS)
    add_subdirectory(examples)
endif()

##############################################
#
# PACKAGING
#
##############################################

# Set packaging variables
#------------------------
set(CPACK_PACKAGE_NAME "dicomhero6")
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
file(WRITE "${SHLIBS_FILE}" "libdicomhero6 ${DICOMHERO_MAJOR_VERSION} ${CPACK_PACKAGE_NAME}\n")
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
     "Copyright (C) 2005-2021 ${CPACK_DEBIAN_PACKAGE_MAINTAINER}")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/copyright"
        DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/"
        PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ
        WORLD_READ)

install(TARGETS dicomhero6 EXPORT dicomhero6Config LIBRARY DESTINATION lib
                                                 ARCHIVE DESTINATION lib
                                                 RUNTIME DESTINATION bin
                                                 PUBLIC_HEADER DESTINATION include
                                                 COMPONENT "DICOMHERO Shared library")

install(FILES ${imebra_interface} DESTINATION include/imebra COMPONENT "DICOMHero legacy include files")
install(FILES ${dicomhero_interface} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")

if("${DICOMHERO_OBJC}" STREQUAL "1")
    install(FILES ${dicomhero_objc_include} DESTINATION include/dicomhero6_objc COMPONENT "DICOMHero objc include files")
endif("${DICOMHERO_OBJC}" STREQUAL "1")

install(EXPORT dicomhero6Config DESTINATION share/dicomhero6/cmake)

include(CPack)
