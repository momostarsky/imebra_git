# Options:
# -DDICOMHERO_SHARED_STATIC=SHARED|STATIC (default = SHARED)
# -DJPEG2000=0|1|2 include JPEG2000 codec (1=version 1.X 2=version2.X)
# -DADDITIONAL_INCLUDE_PATH=path to additional include folders (optional)
# -DADDITIONAL_LIB_PATH=path to additional libraries (optional)
# -DDICOMHERO_CHARSET_CONVERSION=ICONV|JAVA|WINDOWS (default = ICONV on posix, WINDOWS on Windows)
# -DDICOMHERO_OBJC=1|0 (default = 0)
# -DEMBED_BITCODE=1|0 (default = 0)
# -DBUILD_DICOMHERO_DOCUMENTATION=ON|OFF (default = OFF) Build the documentation

cmake_minimum_required(VERSION 3.12)

project("dicomhero6")

set(BUILD_DICOMHERO_DOCUMENTATION OFF CACHE BOOL "Build the documentation")

#
# Use C++11 by default. Set CMAKE_CXX_STANDARD to force other versions.
#
#=========================================================================
if("*${CMAKE_CXX_STANDARD}*" STREQUAL "**")
    set(CMAKE_CXX_STANDARD 11)
endif()

#
# The build type must be explicitly set
#
#=========================================================================
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if("*${CMAKE_BUILD_TYPE}*" STREQUAL "**")
    set(CMAKE_BUILD_TYPE "Debug") # Default build mode is debug
endif()

#
# Generate vcs_version.h
#
#=========================================================================
find_package (Git)
set(VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/vcs_version.h")
set(VERSION_FILE_RAW "${CMAKE_CURRENT_BINARY_DIR}/version.txt")
if (GIT_FOUND)
    message("git found: ${GIT_EXECUTABLE}")
    execute_process(COMMAND "${GIT_EXECUTABLE}" "branch"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE branches OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(REPLACE "\n" ";" branchesList "${branches}")
    foreach(checkBranch ${branchesList})
        message("checking ${checkBranch}")
        string(SUBSTRING ${checkBranch} 0 2 active)
        if("${active}" STREQUAL "* ")
            string(SUBSTRING ${checkBranch} 2 -1 branch)
        endif()
    endforeach()

    execute_process(COMMAND "${GIT_EXECUTABLE}" "rev-parse" "HEAD"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE hash OUTPUT_STRIP_TRAILING_WHITESPACE)

    if(NOT "$ENV{APPVEYOR_REPO_BRANCH}" STREQUAL "")
        set(branch $ENV{APPVEYOR_REPO_BRANCH})
    endif()
    message("Branch ${branch}")

    if((${branch} MATCHES "^[0-9]+\.[0-9.]*[0-9]+$") OR (${branch} MATCHES ".*/[0-9]+\.[0-9.]*[0-9]+$"))
        string(APPEND branch ".0.0.0.0")
        string(REGEX MATCHALL "[0-9]+" major_minor_build "${branch}")
        list(LENGTH major_minor_build version_length)
        list(GET major_minor_build 0 major)
        list(GET major_minor_build 1 minor)
        list(GET major_minor_build 2 patch)
        list(GET major_minor_build 3 build)
    else()
        set(major "0")
        set(minor "0")
        set(patch "0")
        set(build "0")
    endif()

    message("Version ${major}.${minor}.${build}")

    set(version_rc "${major},${minor},${patch},${build}")

    file(WRITE "${VERSION_FILE}" "#ifndef VERSION_FILE\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_FILE\n")
    file(APPEND "${VERSION_FILE}" "#define VCS_COMMIT_SHORTHASH \"${hash}\"\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_MAJOR ${major}\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_MINOR ${minor}\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_PATCH ${patch}\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_BUILD ${build}\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION \"${major}.${minor}.${patch}\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL \"${major}.${minor}.${patch}.${build}\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL_W L\"${major}.${minor}.${patch}.${build}\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_RC \"${version_rc}\"\n")
    file(APPEND "${VERSION_FILE}" "#endif\n")
    file(WRITE "${VERSION_FILE_RAW}" "${major}.${minor}.${patch}.${build}")
else()
    file(APPEND "${VERSION_FILE}" "#ifndef VERSION_FILE\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_FILE\n")
    file(APPEND "${VERSION_FILE}" "#define VCS_COMMIT_SHORTHASH \"Devel\"\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_MAJOR 0\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_MINOR 0\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_PATCH 0\n")
    file(APPEND "${VERSION_FILE}" "#define VERSION_BUILD 0\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION \"0.0.0\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL \"0.0.0.0\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_FULL_W L\"0.0.0.0\"\n")
    file(APPEND "${VERSION_FILE}" "#define PRODUCT_VERSION_RC \"0,0,0,0\"\n")
    file(APPEND "${VERSION_FILE}" "#endif\n")
    file(WRITE "${VERSION_FILE_RAW}" "0.0.0.0")
endif ()
set(DICOMHERO_MAJOR_VERSION ${major})
set(DICOMHERO_VERSION "${major}.${minor}.${patch}.${build}")
include_directories(${CMAKE_CURRENT_BINARY_DIR})


##############################################
#
# DOCUMENTATION
#
##############################################
if(${BUILD_DICOMHERO_DOCUMENTATION})
    find_package (Python3 COMPONENTS Interpreter REQUIRED)
    find_package (Doxygen REQUIRED)
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import jinja2"
        RESULT_VARIABLE JINJA_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import sphinx"
        RESULT_VARIABLE SPHINX_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import breathe"
        RESULT_VARIABLE BREATHE_EXIT_CODE
        OUTPUT_QUIET
    )

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import sphinx_rtd_theme"
        RESULT_VARIABLE SPHINX_RTD_THEME_EXIT_CODE
        OUTPUT_QUIET
    )

    if(NOT ${JINJA_EXIT_CODE} EQUAL 0)
        message("To build the documentation you need to install the python package jinja2 (Preferred version is 3.0.3)")
    endif()

    if(NOT ${SPHINX_EXIT_CODE} EQUAL 0)
        message("To build the documentation you need to install the python package sphinx (Preferred version is 2.4.4)")
    endif()

    if(NOT ${BREATHE_EXIT_CODE} EQUAL 0)
        message("To build the documentation you need to install the python package breathe (Preferred version is 4.14.2)")
    endif()

    if(NOT ${SPHINX_RTD_THEME_EXIT_CODE} EQUAL 0)
        message("To build the documentation you need to install the python package sphinx_rtd_theme")
    endif()

    file(GLOB dicomhero_doc_sources "${CMAKE_SOURCE_DIR}/docs/*.*")
    file(GLOB dicomhero_doc_interface "${CMAKE_SOURCE_DIR}/dicomheroCore6/library/include/dicomhero6/*.h")

    add_custom_target(documentation ALL "sphinx-build" "-b" "html" "${CMAKE_CURRENT_SOURCE_DIR}/docs" "${CMAKE_CURRENT_BINARY_DIR}/docs/html"
        DEPENDS dicomhero6
        SOURCES ${dicomhero_doc_sources}
                ${dicomhero_doc_interface})
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

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal ${HIDDEN_FLAGS}")
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

if(${BUILD_DICOMHERO_DOCUMENTATION})
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs"
            DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/")
endif()

install(FILES ${imebra_interface} DESTINATION include/imebra COMPONENT "DICOMHero legacy include files")
install(FILES ${dicomhero_interface} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")
install(FILES ${VERSION_FILE} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")
install(FILES ${VERSION_FILE_RAW} DESTINATION include/dicomhero6 COMPONENT "DICOMHero include files")

if("${DICOMHERO_OBJC}" STREQUAL "1")
    install(FILES ${dicomhero_objc_include} DESTINATION include/dicomhero6_objc COMPONENT "DICOMHero objc include files")
endif("${DICOMHERO_OBJC}" STREQUAL "1")

install(EXPORT dicomhero6Config DESTINATION share/dicomhero6/cmake)

include(CPack)
