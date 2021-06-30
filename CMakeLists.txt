cmake_minimum_required(VERSION 3.17)
project(BabelLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(
        BabLib STATIC
        babel.hpp)

set_target_properties(BabLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(BabLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(BabelLibrary main.cpp)

target_link_libraries(BabelLibrary PUBLIC BabLib)
#target_compile_options(BabelLibrary PRIVATE -O0)
target_compile_options(BabelLibrary PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
#set(CMAKE_CXX_FLAGS "-target i686-pc-windows-gnu")