project(slime)

add_executable(slime main.cpp)

target_link_libraries(slime tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})