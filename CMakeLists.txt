cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SimpleProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the architecture explicitly (ARM64 for M1/M2 Macs)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64" OR CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# Compiler-specific warning flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(ALL_WARNINGS "-Wall" "-Wextra" "-Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(ALL_WARNINGS "/W4" "/permissive-")
endif()

# Add the main executable
add_executable(SimpleProject src/main.cpp)

# Ensure the correct standard library is used and add warnings
target_compile_options(SimpleProject PRIVATE -stdlib=libc++ ${ALL_WARNINGS})

# Add the math_utils library
add_library(math_utils src/math_utils.cpp)

# Ensure the correct standard library is used for the library and add warnings
target_compile_options(math_utils PRIVATE -stdlib=libc++ ${ALL_WARNINGS})

# Set the CMake policy to the NEW behavior for DOWNLOAD_EXTRACT_TIMESTAMP
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Download the nlohmann/json library
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.2  # Use the appropriate version
)
FetchContent_MakeAvailable(json)

# Add the test executable
add_executable(math_utils_test test/test_math_utils.cpp)
target_link_libraries(math_utils_test gtest gtest_main math_utils)

# Ensure the correct standard library is used for the test executable and add warnings
target_compile_options(math_utils_test PRIVATE -stdlib=libc++ ${ALL_WARNINGS})

# Add the include directory for the math_utils_test target
target_include_directories(math_utils_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Discover and register the tests
include(GoogleTest)
gtest_discover_tests(math_utils_test)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(benchmark)

# Link benchmark with pthread if necessary
find_package(Threads REQUIRED)

# Add the benchmark executable
add_executable(benchmark_example benchmark/benchmark_example.cpp)
target_link_libraries(benchmark_example benchmark::benchmark math_utils Threads::Threads)
target_compile_options(benchmark_example PRIVATE -stdlib=libc++ ${ALL_WARNINGS})

# Ensure the correct standard library is used for the benchmark executable
target_include_directories(benchmark_example PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

target_link_libraries(SimpleProject PRIVATE nlohmann_json::nlohmann_json)
