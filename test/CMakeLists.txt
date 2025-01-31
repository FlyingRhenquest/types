cmake_minimum_required(VERSION 3.25)

project(TypelistTests CXX)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)
include(GoogleTest)

if (NOT TARGET FR::types)
  #
  # If this wasn't included from the top level, it'll
  # look for an installed types package. This allows you
  # to run current unit tests against an already-installed
  # types library
  #
  find_package(FR REQUIRED COMPONENTS types)
endif()
  
set(TEST_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/TypelistTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Concepts.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/AggregateType.cpp
)

add_executable(TypesTests
  ${TEST_SRC}
)

target_link_libraries(TypesTests PUBLIC
  GTest::GTest
  GTest::Main
  FR::types
)
