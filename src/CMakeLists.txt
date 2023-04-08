cmake_minimum_required(VERSION 3.5)

project(FlockingSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlockingSimulation main.cpp)
FILE(COPY ../res/text.png DESTINATION "${CMAKE_BINARY_DIR}")

set(SFML_DIR "SFML/lib/cmake/SFML")
target_link_libraries(FlockingSimulation sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED graphics network audio window system)
