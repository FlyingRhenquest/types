cmake_minimum_required(VERSION 3.25)

project(FRTypes)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS OFF)
option(BUILD_EXAMPLES OFF)

set(HEADER_DIR "include/fr/types")
set(INTERFACE_HEADERS
  "${HEADER_DIR}/AggregateType.h"
  "${HEADER_DIR}/Concepts.h"
  "${HEADER_DIR}/Typelist.h"
)

add_library(types INTERFACE)

# Using PUBLIC_HEADER causes cmake to install the headers.
# If you want to install them in a subdirectory off include
# (Which makes removing them a LOT easier if you ever need to)
# you need to specify in the install(TARGETS ...) command below,
# the specific subdirectory where they should be installed.
# Otherwise they will just end up in include.
set_target_properties(types PROPERTIES
  FRAMEWORK TRUE
  PUBLIC_HEADER "${INTERFACE_HEADERS}"
)

target_include_directories(types
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
  
set(FRTypes_VERSION_MAJOR 0)
set(FRTypes_VERSION_MINOR 1)
set(FRTypes_VERSION ${FRTypes_VERSION_MAJOR}.${FRTypes_VERSION_MINOR})

#
# This alias allows us to treat the target the same way
# when building and using the library
#

add_library(FR::types ALIAS types)

if (BUILD_TESTS)
  add_subdirectory(test)
endif()

if (BUILD_EXAMPLES)
  add_subdirectory(examples/type_association)
  add_subdirectory(examples/factories)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/FRTypesConfigVersion.cmake"
  VERSION "${FRTypes_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/FRTypesConfig.cmake"
  INSTALL_DESTINATION lib/cmake/FRTypes
)

install(TARGETS types
  EXPORT types_export
  DESTINATION include/fr/types
)

install(EXPORT types_export
  FILE FRTypesTargets.cmake
  NAMESPACE FR::
  DESTINATION lib/cmake/FRTypes
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/FRTypesConfigVersion.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/FRTypesConfig.cmake"
  DESTINATION lib/cmake/FRTypes
)
