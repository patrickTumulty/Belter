cmake_minimum_required(VERSION 3.10)

project(runtime VERSION 0.1.0 LANGUAGES C)

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
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE prayengine)

