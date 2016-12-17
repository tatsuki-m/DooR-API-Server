cmake_minimum_required(VERSION 2.8)

# release build option 
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")

# debug build option
set(CMAKE_CXX_FLAGS_DEBUG "-g")

#set build type
set(CMAKE_BUILD_TYPE Release)

# set project name
project(door_shared_memory)

# set version
set(serial "1.0.0")

# set sharead library version
set(soserial "1")

# include file
file(GLOB Cpps "./*.cpp")
file(GLOB Headers "./*.h")

# specify header file place
include_directories("${PROJECT_SOURCE_DIR}")

# build as shared library
add_library(door_shared_memory SHARED ${Cpps})

# apply library version
set_target_properties(door_shared_memory PROPERTIES VERSION ${serial} SOVERSION ${soserial})

# specify install of shared library
# /usr/local/lib
install(TARGETS door_shared_memory LIBRARY DESTINATION lib)

# specify install of header file for shared library
# /usr/local/include
install(FILES ${Headers} DESTINATION include)

