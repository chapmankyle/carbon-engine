cmake_minimum_required( VERSION 3.11.0 )
set( CMAKE_SUPPRESS_REGENERATION ON )
set( CMAKE_INSTALL_MESSAGE LAZY )

# set project name and root dir
project( "Carbon Engine" )

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
