cmake_minimum_required(VERSION 3.5)

project(FlockingSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/SFML)

add_executable(FlockingSimulation src/main.cpp src/Application.cpp src/Boid.cpp src/Flock.cpp)
FILE(COPY res/text.png DESTINATION "${CMAKE_BINARY_DIR}")

target_include_directories(FlockingSimulation PUBLIC src/SFML/include)

target_link_directories(FlockingSimulation PRIVATE src/SFML/src)

target_link_libraries(FlockingSimulation sfml-graphics)
