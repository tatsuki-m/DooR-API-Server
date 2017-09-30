cmake_minimum_required(VERSION 2.8)

# packet information"
set (PROJECT_NAME "door_ipc")

# avoid cmake warning
cmake_policy(SET CMP0022 NEW)

# set project name
project(${PROJECT_NAME})

# release build option 
set(CMAKE_CXX_FLAGS_RELEASE "-Wall")

# debug build option
set(CMAKE_CXX_FLAGS_DEBUG "-g")

#set build type
set(CMAKE_BUILD_TYPE Release)

# set version
set(serial "1.0.0")

# set sharead library version
set(soserial "1")

# add src dir and build dir to INTERFACE_INCLUDE_DIRECTORIES
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# include file
file(GLOB Srcs "./src/*.cpp")
file(GLOB PUBLIC_HDRS "./src/*.h")

# specify header file place
include_directories("${PROJECT_SOURCE_DIR}")

# build as shared library
add_library(${PROJECT_NAME} SHARED ${Srcs})

# apply library version
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${serial}
    SOVERSION ${soserial}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${PUBLIC_HDRS}")

# specify install of shared library
# /usr/local/lib
install(TARGETS door_ipc
    EXPORT          door_ipc_export
    LIBRARY         DESTINATION lib
    INCLUDES        DESTINATION include
    PUBLIC_HEADER   DESTINATION "include/${PROJECT_NAME}")

# door_ipc-config.cmake
install(EXPORT door_ipc_export
    FILE door_ipc-config.cmake
    DESTINATION "share/cmake/${PROJECT_NAME}/"
    EXPORT_LINK_INTERFACE_LIBRARIES)

