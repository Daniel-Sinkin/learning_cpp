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

# Set Clang++ as the linker
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_LINKER clang++)

# Add the executable
add_executable(SimpleProject src/main.cpp)

# Ensure the correct standard library is used
target_compile_options(SimpleProject PRIVATE -stdlib=libc++)
