cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Client)

set(Client "Client")

project(${Client} VERSION 17.12.24)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()

#file(GLOB net "src/net/*.h" "src/net/*.hpp" "src/net/*.cpp" "src/net/*.c")
#file(GLOB classes "src/classes/*.h" "src/classes/*.hpp" "src/classes/*.cpp" "src/classes/*.c")
file(GLOB src "*.h" "*.hpp" "*.c" "*.cpp")
file(GLOB net "../net/*.h" "../net/*.hpp" "../net/*.cpp" "../net/*.c")
#file(GLOB enums "src/enums/*.h" "src/enums/*.hpp" "src/enums/*.cpp" "src/enums/*.c")
#file(GLOB imgui "src/imgui/*.h" "src/imgui/*.hpp" "src/imgui/*.cpp""src/imgui/*.c")
#add_executable(${Client} ${src} ${imgui} ${classes} ${enums})

add_executable(${Client} ${src} ${net})

#set(COMMON_SOURCES common/socketWrapper.h common/color.h)
#set(CLIENT_SOURCES main.hpp )

#add_executable(${Client} ${CLIENT_SOURCES})

#include(CMakePrintHelpers)
#cmake_print_variables("TEST!!!")

#include_directories("${CMAKE_SOURCE_DIR}/include")
#link_directories(${CMAKE_SOURCE_DIR}/lib)

