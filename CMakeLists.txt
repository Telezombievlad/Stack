set(PROJECT_NAME "Stack")

if(${PROJECT_NAME} STREQUAL "Sample Project Name")
	message(AUTHOR_WARNING "No project name is set")
endif()

project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Weverything --std=c++14 -stdlib=libc++ -Wno-c++98-compat -Wno-padded -Wno-switch-enum")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

# file(GLOB_RECURSE TEST_SOURCES "src/main.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")

# include_directories(SYSTEM /usr/local/include/SDL2)
# link_libraries(sdl2 sdl2_ttf sdl2_net sdl2_mixer sdl2_image)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/res COMMAND ln -s ${CMAKE_BINARY_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# add_library(${PROJECT_NAME} STATIC ${SOURCES})
# add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
