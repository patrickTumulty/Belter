cmake_minimum_required(VERSION 3.10)

project(belter VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True) # Optional, but recommended

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TMEM_TRACK)
endif()

add_subdirectory(libs/prayengine)

include_directories(src)

file(GLOB SOURCES
    src/main.c
    src/shape_system.c
    src/init_system.c
    src/camera_system.c
    src/physics_system.c
    src/components.c
    src/player_controller_system.c
    src/background_system.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dist/bin"
)

configure_file(
    ${CMAKE_SOURCE_DIR}/runtime/gamecontrollerdb.txt 
    ${CMAKE_BINARY_DIR}/dist/runtime/gamecontrollerdb.txt 
    COPYONLY
)

configure_file(
    ${CMAKE_SOURCE_DIR}/scripts/start.sh
    ${CMAKE_BINARY_DIR}/dist/start.sh
    COPYONLY
)

target_link_libraries(${PROJECT_NAME} PRIVATE prayengine)

