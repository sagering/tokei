project(headless_compute)

add_executable(headless_compute headless_compute.cpp)

target_link_libraries(headless_compute tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})