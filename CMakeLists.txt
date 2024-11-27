cmake_minimum_required(VERSION 3.14)

project(BrighteningTest VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17 and enforce it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest (and GoogleMock) as a dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Force GoogleTest to use the shared CRT for Windows compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Define the source files for the project
set(SOURCES
    brightener.cpp
    image.cpp       # Ensure image.cpp is included, as it's required
)

# Create the test executable
add_executable(brightening-test
    brightening-test/brightening-test.cpp  # Include the test file
    ${SOURCES}                             # Include the sources (brightener.cpp, image.cpp)
)

# Add the include directories for the project (where header files are located)
target_include_directories(brightening-test PRIVATE
    ${CMAKE_SOURCE_DIR}  # Include the project root as an include directory
)

# Link the required libraries for GoogleTest
target_link_libraries(brightening-test
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    GTest::gmock_main
)

# Discover and run the tests using GoogleTest
include(GoogleTest)
gtest_discover_tests(brightening-test)
