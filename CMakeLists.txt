cmake_minimum_required(VERSION 3.1)
project(behavior_decision_pomdp)

set(CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

add_executable(behavior_decision_pomdp ${SRC})