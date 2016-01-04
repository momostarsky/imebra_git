cmake_minimum_required(VERSION 2.8)

project("imebra")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wpedantic -Wconversion -Wfloat-equal -fvisibility=hidden -fvisibility-inlines-hidden")

add_definitions(-DIMEBRA_DLL)
add_definitions(-DIMEBRA_DLL_EXPORTS)

include_directories(include)

file(GLOB imebra_interface "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h")
file(GLOB imebra_include "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB imebra_src "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB imebra_implementation_src "${CMAKE_CURRENT_SOURCE_DIR}/implementation/*.cpp")
file(GLOB imebra_implementation_include "${CMAKE_CURRENT_SOURCE_DIR}/implementation/*.h")


add_library(imebra SHARED
    ${imebra_implementation_src}
    ${imebra_implementation_include}
    ${imebra_include}
    ${imebra_src}
    ${imebra_interface}
)

# Set the library version from IMEBRA_MAJOR_VERSION, IMEBRA_MINOR_VERSION,
#  & IMEBRA_REVISION
#---------------------------------------------------------------------------------
if ("$ENV{IMEBRA_MAJOR_VERSION}" STREQUAL "")
    set(IMEBRA_MAJOR_VERSION "1")
else("$ENV{IMEBRA_MAJOR_VERSION}" STREQUAL "")
    set(IMEBRA_MAJOR_VERSION "$ENV{IMEBRA_MAJOR_VERSION}")
endif("$ENV{IMEBRA_MAJOR_VERSION}" STREQUAL "")

if ("$ENV{IMEBRA_MINOR_VERSION}" STREQUAL "")
    set(IMEBRA_MINOR_VERSION "0")
else("$ENV{IMEBRA_MINOR_VERSION}" STREQUAL "")
    set(IMEBRA_MINOR_VERSION "$ENV{IMEBRA_MINOR_VERSION}")
endif("$ENV{IMEBRA_MINOR_VERSION}" STREQUAL "")

if ("$ENV{IMEBRA_REVISION}" STREQUAL "")
    set(IMEBRA_REVISION "0")
else("$ENV{IMEBRA_REVISION}" STREQUAL "")
    set(IMEBRA_REVISION "$ENV{IMEBRA_REVISION}")
endif("$ENV{IMEBRA_REVISION}" STREQUAL "")

set(IMEBRA_VERSION "${IMEBRA_MAJOR_VERSION}.${IMEBRA_MINOR_VERSION}.${IMEBRA_REVISION}")

set_target_properties(imebra PROPERTIES VERSION ${IMEBRA_VERSION}
                                          SOVERSION ${IMEBRA_MAJOR_VERSION})

# Set packaging variables
#------------------------
set(CPACK_PACKAGE_NAME "libimebra${IMEBRA_MAJOR_VERSION}")
set(CPACK_PACKAGE_CONTACT "paolo@binarno.com")
set(CPACK_PACKAGE_VERSION ${IMEBRA_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Imebra library for DICOM medical files")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../readme.md")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://imebra.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Paolo Brandoli <paolo@binarno.com>")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

set(CPACK_RPM_PACKAGE_REQUIRES "libc6")


target_link_libraries(imebra pthread)

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
file(WRITE "${SHLIBS_FILE}" "libimebra ${IMEBRA_MAJOR_VERSION} ${CPACK_PACKAGE_NAME}\n")
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
     "Copyright (C) 2015 ${CPACK_DEBIAN_PACKAGE_MAINTAINER}")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/copyright"
        DESTINATION "share/doc/${CPACK_PACKAGE_NAME}/"
        PERMISSIONS
        OWNER_WRITE OWNER_READ
        GROUP_READ
        WORLD_READ)

install(TARGETS imebra LIBRARY DESTINATION lib COMPONENT "Shared library")

install(FILES ${imebra_include} DESTINATION include/imebra COMPONENT "Include files")

include(CPack)
