cmake_minimum_required(VERSION 3.20)
project(ARP C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



option(BUILD_FOR_WINDOWS "Cross-compile for Windows using MinGW" OFF)


include(FetchContent)

set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
)

# Raylib build options
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

if(BUILD_FOR_WINDOWS)
    set(PLATFORM Desktop CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(raylib)


file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)


if(BUILD_FOR_WINDOWS)
    # Link the Windows subsystem (no console window)
    target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
    target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".exe"
    )
else()
    # link for Linux
    target_link_libraries(${PROJECT_NAME} PRIVATE m dl pthread)
    find_package(X11)
    if(X11_FOUND)
        target_link_libraries(${PROJECT_NAME} PRIVATE X11)
    endif()
endif()


install(TARGETS ${PROJECT_NAME} DESTINATION bin)