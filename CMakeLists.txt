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

# Add the main executable
add_executable(SimpleProject src/main.cpp)

# Ensure the correct standard library is used
target_compile_options(SimpleProject PRIVATE -stdlib=libc++)

# Add the math_utils library
add_library(math_utils src/math_utils.cpp)

# Ensure the correct standard library is used for the library
target_compile_options(math_utils PRIVATE -stdlib=libc++)

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
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(math_utils_test test/test_math_utils.cpp)

# Link the test executable with GoogleTest and math_utils library
target_link_libraries(math_utils_test gtest gtest_main math_utils)

# Ensure the correct standard library is used for the test executable
target_compile_options(math_utils_test PRIVATE -stdlib=libc++)

# Add the include directory for the math_utils_test target
target_include_directories(math_utils_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Discover and register the tests
include(GoogleTest)
gtest_discover_tests(math_utils_test)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
