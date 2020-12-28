# Copyright 2016-2020 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

# Avoid a warning if parent project sets VERSION in project().
if (${CMAKE_VERSION} VERSION_GREATER "3.0.1")
	cmake_policy(SET CMP0048 NEW)
endif()

project(SPIRV-Cross LANGUAGES CXX C)

option(SPIRV_CROSS_WERROR "Fail build on warnings." OFF)
option(SPIRV_CROSS_MISC_WARNINGS "Misc warnings useful for Travis runs." OFF)

set(spirv-compiler-options "")
set(spirv-compiler-defines "")
set(spirv-cross-link-flags "")

if (SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS)
	set(spirv-compiler-defines ${spirv-compiler-defines} SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS)
	if (NOT MSVC)
		set(spirv-compiler-options ${spirv-compiler-options} -fno-exceptions)
	endif()
endif()

if (WIN32)
	set(CMAKE_DEBUG_POSTFIX "d")
endif()

if (CMAKE_COMPILER_IS_GNUCXX OR ((${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND NOT MSVC))
	set(spirv-compiler-options ${spirv-compiler-options} -Wall -Wextra -Wshadow -Wno-deprecated-declarations)
	if (SPIRV_CROSS_MISC_WARNINGS)
		if (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
			set(spirv-compiler-options ${spirv-compiler-options} -Wshorten-64-to-32)
		endif()
	endif()
	if (SPIRV_CROSS_WERROR)
		set(spirv-compiler-options ${spirv-compiler-options} -Werror)
	endif()
elseif (MSVC)
	set(spirv-compiler-options ${spirv-compiler-options} /wd4267 /wd4996)
endif()

set(spirv-cross-core-sources
		${CMAKE_CURRENT_SOURCE_DIR}/GLSL.std.450.h
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_common.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross_containers.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross_error_handling.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_parser.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_parser.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross_parsed_ir.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cross_parsed_ir.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cfg.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/spirv_cfg.cpp)


add_library(spirv-cross-core STATIC ${spirv-cross-core-sources})
target_include_directories(spirv-cross-core PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(spirv-cross-core PRIVATE ${spirv-compiler-options})
target_compile_definitions(spirv-cross-core PRIVATE ${spirv-compiler-defines})

set(spirv-cross-abi-major 0)
set(spirv-cross-abi-minor 39)
set(spirv-cross-abi-patch 0)