cmake_minimum_required(VERSION 3.10)

# set the project name
project(examples)

# add the executable
add_executable(examples main.cpp basic.h basic.cpp suzanne.h suzanne.cpp)

target_link_libraries(examples tokei glfw glm)


file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
