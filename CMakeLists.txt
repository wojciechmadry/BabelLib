cmake_minimum_required(VERSION 3.17)
project(BabelLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(
        BabLib STATIC
        babel.hpp)

set_target_properties(BabLib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(BabLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(BabelLibrary main.cpp)

if(UNIX)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(BabelLibrary PRIVATE Threads::Threads)
endif(UNIX)

target_link_libraries(BabelLibrary PUBLIC BabLib)
#target_compile_options(BabelLibrary PRIVATE -O3)
target_compile_options(BabelLibrary PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)