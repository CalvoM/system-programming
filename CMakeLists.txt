cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(P_NAME "system_programming")
set(DESC "Practising system programming")
file(GLOB_RECURSE c_files ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB_RECURSE source_include ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.c)
project(${P_NAME} VERSION 1.0 DESCRIPTION ${DESC} LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/includes)
add_executable(mmcp memory_mappings/mmcp.c ${source_include})
