cmake_minimum_required( VERSION 3.11.0 )
set( CMAKE_SUPPRESS_REGENERATION ON )
set( CMAKE_INSTALL_MESSAGE LAZY )

# set project name and root dir
project( "CarbonEngine" )

set( CARBON_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# specify command-line options
option( IS_RELEASE "IS_RELEASE specifies if the build is for Release (1) or Debug (0)." OFF )
option( ENABLE_MULTICORE "ENABLE_MULTICORE will allow MSVC to use multiple cores, if ON, by adding the /MP argument." ON )

# show specified options
message( STATUS "----- Build Settings -----" )
message( STATUS "Compiler=${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}" )
message( STATUS "IS_RELEASE=${IS_RELEASE}" )
message( STATUS "ENABLE_MULTICORE=${ENABLE_MULTICORE}" )

if( IS_RELEASE )
	message( STATUS "=> Building for Release!" )
	add_definitions( -DCARBON_DISABLE_DEBUG )
	set( CMAKE_BUILD_TYPE Release )
else()
	message( STATUS "=> Building for Debug!" )
	set( CMAKE_BUILD_TYPE Debug )
endif()
message( STATUS "--------------------------" )

# specify C++ standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# add generated files to directory
set( GENERATED_INC_DIR ${CMAKE_BINARY_DIR}/gen )
message( STATUS "Generated directory : ${GENERATED_INC_DIR}" )

# add CMake directory to module path
list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake" )
message( STATUS "CMake module path : ${CMAKE_MODULE_PATH}" )

# Visual Studio
if( MSVC )
	add_definitions( -D_CRT_SECURE_NO_WARNINGS )

	if( ENABLE_MULTICORE )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP" )
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
	endif()

# GCC
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
	add_definitions( -fPIC )

# Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_definitions( -fPIC )
endif()

# include submodules
add_subdirectory( deps/glfw-bin )
include_directories( deps/glfw-bin/include )

add_subdirectory( deps/glm )
include_directories( deps/glm )
