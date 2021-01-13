project(pbr)

add_executable(pbr pbr.cpp)

target_link_libraries(pbr tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})