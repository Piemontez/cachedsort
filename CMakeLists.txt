cmake_minimum_required(VERSION 3.1.0)

project(cachedsort VERSION 0.1.0 DESCRIPTION "CachedSort Test")

set(CMAKE_BUILD_TYPE Debug)
file(GLOB SOURCES "*.cpp")

#definitions
#add_definitions(-DCOUNT_OPERATION) #Comment this line to not show the total operations


#flags
#c++11flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)

set(INSTALL_DIR      "${CMAKE_CURRENT_BINARY_DIR}/dist")
set(INSTALL_BIN_DIR  "${NSTALL_DIR}/bin")

message(STATUS "INSTALL_DIR = ${INSTALL_DIR}")

#compilerflag
IF(RELEASE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -o2")
ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g")
ENDIF()

#includes
include_directories(
    include
) 

#file to builder
add_executable(cachedsort
    src/main.cpp
    src/tools.cpp
    src/algorithms.cpp
    src/cachedsort.cpp
    src/cachedsort2.cpp
    src/cachedsort3.cpp
)

install(TARGETS cachedsort 
    RUNTIME DESTINATION ${INSTALL_BIN_DIR})