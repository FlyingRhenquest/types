cmake_minimum_required(VERSION 3.25)

project(FactoriesExample)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# If we're building the example outside the library
# we'll want to find the package
if (NOT TARGET FR::types)
  find_package(FRTypes)
endif()

add_executable(Factories
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

target_link_libraries(Factories PRIVATE FR::types)

