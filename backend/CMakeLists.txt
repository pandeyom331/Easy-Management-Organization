cmake_minimum_required(VERSION 3.10)
project(Easy_Management_Organization_backend)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow (header-only): assuming you placed it in "Crow/include"
include_directories(${CMAKE_SOURCE_DIR}/Crow)

# Find Boost (only headers used by Crow)
find_package(Boost REQUIRED)

# JSON for Modern C++
find_package(nlohmann_json REQUIRED)

# Main backend executable
add_executable(Easy-Management-Organization-backend
    main.cpp
)

# Link threads + header-only libraries (Boost and nlohmann_json)
target_link_libraries(Easy-Management-Organization-backend
    pthread
    Boost::boost
    nlohmann_json::nlohmann_json
)
