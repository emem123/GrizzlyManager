cmake_minimum_required(VERSION 2.8)
project(GrizzlyManager)
file(GLOB_RECURSE helloworld_SRC "src/*.c" "src/*.cpp")

add_executable(grizzlymanager  ${helloworld_SRC})
TARGET_LINK_LIBRARIES(grizzlymanager dl pthread)
