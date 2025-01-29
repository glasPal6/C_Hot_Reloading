cmake_minimum_required(VERSION 3.25)
project(Hot_Reloading)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PLUG_NAME plug)
set(BUILD_NAME main)

option(HOTRELOAD_ENABLE "Enable hot reloading" ON)

#----------------------------------------------
# Plug build
#----------------------------------------------

# Custom command to generate src/plug.c
add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/src/plug.c
    COMMAND ${CMAKE_COMMAND} -E echo "#include \"plug.h\"" > ${CMAKE_SOURCE_DIR}/src/plug.c
    DEPENDS ${CMAKE_SOURCE_DIR}/src/plug.h
    COMMENT "Generating plug.c"
    VERBATIM
)

# Define the library target, using the generated src/plug.c
add_library(${PLUG_NAME}
SHARED
    src/plug.c
)

# Needed to build the library
target_compile_definitions(${PLUG_NAME}
PRIVATE
    PLUG_IMPLEMENTATION
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

# Custom command to remove src/plug.c after the build completes
add_custom_command(
    TARGET ${PLUG_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/src/plug.c
    COMMENT "Removing src/plug.c"
    VERBATIM
)

#----------------------------------------------

#----------------------------------------------
# Main build
#----------------------------------------------

add_executable(${BUILD_NAME} src/main.c)

# If Hot Reloading is enabled
if (HOTRELOAD_ENABLE)
    target_compile_definitions(${BUILD_NAME}
    PRIVATE
        HOTRELOAD
        HOTRELOAD_IMPLEMENTATION
    )
endif()

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

