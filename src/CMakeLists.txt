cmake_minimum_required(VERSION 3.5)

project(FlockingSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlockingSimulation main.cpp Application.cpp Boid.cpp Flock.cpp)
FILE(COPY ../res/text.png DESTINATION "${CMAKE_BINARY_DIR}")

FILE(GLOB_RECURSE LibFiles "*.hpp")
add_custom_target(headers SOURCES ${LibFiles})

target_link_libraries(FlockingSimulation sfml-graphics)

include_directories(${CMAKE_CURRENT_LIST_DIR}/SFML/include)
target_link_libraries(FlockingSimulation ${CMAKE_CURRENT_LIST_DIR}/SFML/lib)

find_package(SFML REQUIRED graphics network audio window system)
