cmake_minimum_required(VERSION 3.12.0)

set(Server "Server")


project(${Server} VERSION 17.12.24)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )

#file(GLOB net "src/net/*.h" "src/net/*.hpp" "src/net/*.cpp" "src/net/*.c")
#file(GLOB classes "src/classes/*.h" "src/classes/*.hpp" "src/classes/*.cpp" "src/classes/*.c")
file(GLOB src "*.h" "*.hpp" "*.c" "*.cpp")
file(GLOB net "../net/*.h" "../net/*.hpp" "../net/*.cpp" "../net/*.c")
#file(GLOB src "src/server/*.h" "src/server/*.hpp" "src/server/*.cpp" "src/server/*.c")
#file(GLOB enums "src/enums/*.h" "src/enums/*.hpp" "src/enums/*.cpp" "src/enums/*.c")
#file(GLOB imgui "src/imgui/*.h" "src/imgui/*.hpp" "src/imgui/*.cpp""src/imgui/*.c")
#add_executable(${Server} ${src} ${imgui} ${classes} ${enums})
add_executable(${Server} ${src} ${net})

#set(COMMON_SOURCES common/socketWrapper.h common/color.h)
#set(SERVER_SOURCES main.hpp )

#add_executable(client ${SERVER_SOURCES})

#include_directories(include)
#link_directories(${CMAKE_SOURCE_DIR}/lib)


#if (WIN32)
    #target_link_libraries(My_Application openal32) #как в папке lib
    #target_link_libraries(${Server} ${CMAKE_SOURCE_DIR}/lib/OpenAL32.lib)
    #target_link_libraries(${Server} glfw3) #как в папке lib
    #target_link_libraries(${Server} ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)  
    #SET(ResTarget ${CMAKE_CURRENT_SOURCE_DIR}/resources/Voxy.res)
    #SET_TARGET_PROPERTIES(${Server} PROPERTIES LINK_FLAGS ${ResTarget})
#endif (WIN32)

#target_link_libraries(${Server} Vulkan::Vulkan)
