cmake_minimum_required(VERSION 3.12.0)

set(ProjectName "KatrielNet")
project(${ProjectName} VERSION 17.12.24)

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory("src/client")
add_subdirectory("src/server")

add_custom_target(${ProjectName})
add_dependencies(${ProjectName} Client Server)

