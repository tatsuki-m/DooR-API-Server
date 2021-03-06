cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_VERBOSE_MAKEFILE 1)

# set project name
project(DooR-API-Server)

# try enalble c++11
# g++ need flags to enable c++11
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" HAS_CPP11)
if (HAS_CPP11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11 -pthread -lrt")
endif()

# search file and insert value to first argument, APISrcs
file(GLOB APISrcs "./src/*.cpp")

# add includes for all
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

# add door shared door_api 
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/door_api")
include_directories("${door_api_SOURCE_DIR}/src")
set(CMAKE_LIBRARY_PATH "${door_api_BINNARY_DIR}" ${CMAKE_LIBRARY_PATH})

# add door door_unix_domain_socket
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/unix_domain_socket_client")
include_directories("${unix_domain_socket_client_SOURCE_DIR}/src")
set(CMAKE_LIBRARY_PATH "${unix_domain_socket_client_BINNARY_DIR}" ${CMAKE_LIBRARY_PATH})

# add door shared door_ipc
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/door_ipc")
# add includes for door_ipc
include_directories("${door_ipc_SOURCE_DIR}/src")
# add library path for door_ipc
set(CMAKE_LIBRARY_PATH "${door_ipc_BINNARY_DIR}" ${CMAKE_LIBRARY_PATH})

# select executable file
# add_executable(<exe-file>, files)
add_executable(DooR-API-Server ${APISrcs})
target_link_libraries(DooR-API-Server door_unix_domain_socket_client)
target_link_libraries(DooR-API-Server door_api)
# use rt option for avoidingk undefied reference to shm_open
# https://stackoverflow.com/questions/31147129/undefined-reference-to-shm-open-using-cmake
target_link_libraries(DooR-API-Server door_ipc rt)

