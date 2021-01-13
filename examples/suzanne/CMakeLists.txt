project(suzanne)

add_executable(suzanne suzanne.cpp)

target_link_libraries(suzanne tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})