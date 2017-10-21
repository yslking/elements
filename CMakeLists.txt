cmake_minimum_required(VERSION 3.4)
project (photon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################

add_subdirectory(lib/libui)

###############################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/libui)

add_executable(hello main.cpp)
target_link_libraries(hello libui)
