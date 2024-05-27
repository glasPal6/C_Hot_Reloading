cmake_minimum_required(VERSION 3.25)
project(Hot_Reloading)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PLUG_NAME plug)
set(BUILD_NAME main)

#----------------------------------------------
# Plug build
#----------------------------------------------
add_library(${PLUG_NAME}
SHARED
    src/plug.c
)

target_include_directories(${PLUG_NAME}
PRIVATE
    raylib/include
)

target_link_libraries(${PLUG_NAME}
    raylib
)

target_compile_options(${PLUG_NAME} 
PRIVATE 
    -Wall 
    -Werror 
    -Wextra
)
#----------------------------------------------

#----------------------------------------------
# Main build
#----------------------------------------------
add_executable(${BUILD_NAME}
    src/main.c
    src/hotreload.c
)

target_compile_definitions(${BUILD_NAME}
PRIVATE
    HOTRELOAD
)

target_include_directories(${BUILD_NAME}
PRIVATE
    raylib/include
)

target_link_libraries(${BUILD_NAME}
    plug
    raylib
)

target_compile_options(${BUILD_NAME} 
PRIVATE 
    -Wall 
    -Werror 
    -Wextra
)
#----------------------------------------------

