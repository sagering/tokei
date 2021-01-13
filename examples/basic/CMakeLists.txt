project(basic)

add_executable(basic basic.cpp)

target_link_libraries(basic tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})