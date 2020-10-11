cmake_minimum_required(VERSION 3.3)

# Project name and version
project(AVL_TREE VERSION 1.0)

# Add local headers
include_directories(include)
set(CMAKE_BUILD_TYPE Release)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

############# SOURCES FOR EXECUTABLE ##########
# Add sources for executable
# set(SOURCES test/main.cpp src/AVL_tree.cpp)
file(GLOB SOURCES_EXE "src/*.cpp" "test/*.cpp")

add_compile_options("-W" "-Wall" "-pedantic")

# Add executable
add_executable(exe ${SOURCES_EXE})

# Add GTest target link libraries to executable exe
target_link_libraries(exe ${GTEST_LIBRARIES} pthread)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)