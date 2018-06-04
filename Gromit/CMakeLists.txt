cmake_minimum_required (VERSION 2.6.3)
project (Gromit C)
set (versioin 1.0)

# Create library and executable
add_library (gromit STATIC gromit.c gromit.h)
add_executable (gromit-gen gromit-gen.c)

# Install and export the targets
install (FILES  gromit.h DESTINATION include/gromit_${version})
install (TARGETS gromit gromit-gen
         DESTINATION lib/gromit-${version}
         EXPORT  gromit-targets)
install (EXPORT gromit-targets
         DESTINATION lib/gromit-${version})
# Create and install package configuration and version files.
configure_file (
    ${Gromit_SOURCE_DIR}/pkg/gromit-config.cmake.in
    ${Gromit_BINARY_DIR}/pkg/gromit-config.cmake @ONLY)

configure_file (
    ${Gromit_SOURCE_DIR}/gromit-config-version.cmake.in
    ${Gromit_BINARY_DIR}/gromit-config-version.cmake @ONLY)
install (FILES ${Gromit_BINARY_DIR}/pkg/gromit-config.cmake
    ${Gromit_BINARY_DIR}/gromit-config-version.cmake
    DESTINATION lib/gromit-${version})

