cmake_minimum_required (VERSION 2.6)
project(lets_boost)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # For VS to organize the project in folders

# We need C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
# But that seems to fail sometimes so we also add this flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -O0 -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline") #MSVC will ignore these additional flags
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

message ("cxx flags: " ${CMAKE_CXX_FLAGS})

file (GLOB SOURCES "src/*.cpp" "src/*.h")
#file (GLOB TEST_SOURCES "src/tests/*.h")

source_group ("src" FILES ${SOURCES})
#source_group ("src/tests" FILES ${TEST_SOURCES})

#add boost
set(Boost_USE_STATIC_LIBS 		ON) 
set(Boost_USE_MULTITHREADED 	ON)  
set(Boost_USE_STATIC_RUNTIME 	OFF) 
find_package(Boost 1.61.0 COMPONENTS program_options date_time serialization chrono) 
find_package(OpenCL REQUIRED)

INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 

LINK_DIRECTORIES(${OpenCL_LIBRARY})
if(Boost_FOUND AND OpenCL_FOUND)
	set (VERSION_NUMBER 0.1)

	if (WIN32)
		set(PLATFORM _WIN32)
	else()
		set(PLATFORM _LINUX)
	endif()

	configure_file (
	  "${PROJECT_SOURCE_DIR}/cmake/config.h.in" #The template to generate the actual header
	  "${PROJECT_SOURCE_DIR}/src/generated/config.h"
	)

    include_directories(SYSTEM ${Boost_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
	add_executable(lets_boost ${SOURCES} ${TEST_SOURCES})
    target_link_libraries(lets_boost ${Boost_LIBRARIES} ${OpenCL_LIBRARIES})
	
	message ("-- Using OpenCL: " ${OpenCL_VERSION_STRING})

elseif(NOT OpenCL_FOUND)
    error("Could not find opencl")
else()
	error("Could not find boost")
endif()

