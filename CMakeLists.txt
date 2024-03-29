cmake_minimum_required(VERSION 3.13)
project(jam)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_program(MOLD_LINKER_EXE mold)

if(MOLD_LINKER_EXE)
#If mold is found, set the linker flags to use it
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=mold")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=mold")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fuse-ld=mold")
else()
#If mold is not found, print a warning message and use the default linker
    message(WARNING "mold linker not found on this system. Using default linker instead.")
endif()

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

add_subdirectory(thirdparty/spdlog)
add_subdirectory(thirdparty/uvw)
add_subdirectory(thirdparty/flecs)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}
    src
    includes/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog
    flecs::flecs_static
    uv
    uvw
)
