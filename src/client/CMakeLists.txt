cmake_minimum_required(VERSION 3.12.0)

set(ProjectName "Client")


project(${ProjectName} VERSION 17.12.24)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )

#file(GLOB net "src/net/*.h" "src/net/*.hpp" "src/net/*.cpp" "src/net/*.c")
#file(GLOB classes "src/classes/*.h" "src/classes/*.hpp" "src/classes/*.cpp" "src/classes/*.c")
file(GLOB src "src/client/*.h" "src/client/*.hpp" "src/client/*.cpp" "src/client/*.c")
#file(GLOB enums "src/enums/*.h" "src/enums/*.hpp" "src/enums/*.cpp" "src/enums/*.c")
#file(GLOB imgui "src/imgui/*.h" "src/imgui/*.hpp" "src/imgui/*.cpp""src/imgui/*.c")
#add_executable(${ProjectName} ${src} ${imgui} ${classes} ${enums})
add_executable(${ProjectName} ${src} )

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/lib)


if (WIN32)
    #target_link_libraries(My_Application openal32) #как в папке lib
    #target_link_libraries(${ProjectName} ${CMAKE_SOURCE_DIR}/lib/OpenAL32.lib)
    #target_link_libraries(${ProjectName} glfw3) #как в папке lib
    #target_link_libraries(${ProjectName} ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)  
    #SET(ResTarget ${CMAKE_CURRENT_SOURCE_DIR}/resources/Voxy.res)
    #SET_TARGET_PROPERTIES(${ProjectName} PROPERTIES LINK_FLAGS ${ResTarget})
endif (WIN32)

#target_link_libraries(${ProjectName} Vulkan::Vulkan)
