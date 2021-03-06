project(multiple_objects)

add_executable(multiple_objects multiple_objects.cpp)

target_link_libraries(multiple_objects tokei glfw glm)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})