cmake_minimum_required(VERSION 3.10)

# set the project name
project(tokei)

# add the executable
add_library(tokei STATIC)

target_include_directories(tokei
	PUBLIC
		$<INSTALL_INTERFACE:include>    
        	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
        	${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/third_party
)
	
target_sources(tokei
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/vk_init.h
		${CMAKE_CURRENT_SOURCE_DIR}/include/pokei.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/pokei.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/resources.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/allocators.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/allocators.cpp
)

target_link_libraries(tokei
	PRIVATE
		spirv-cross-core
)
        
add_subdirectory(third_party)
add_subdirectory(examples)

