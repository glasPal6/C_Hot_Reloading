cmake_minimum_required(VERSION 3.25)
project(Hot_Reloading)
set(BUILD_NAME main)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_executable(${BUILD_NAME}
    src/main.c
)

target_include_directories(${BUILD_NAME}
PRIVATE
    raylib/include
)

find_library(raylib raylib/lib)
target_link_libraries(${BUILD_NAME}
PRIVATE
    libraylib.so
)

target_compile_options(${BUILD_NAME} 
PRIVATE 
    -Wall 
    -Werror 
    -Wextra
)

