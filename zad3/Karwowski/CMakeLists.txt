cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_BUILD_TYPE Debug)


project(zad3)

set(SOURCE_FILES
	src/ReaderWriter.cpp
        src/main.cpp)

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
add_executable( zad3 ${SOURCE_FILES} )
target_link_libraries( zad3 ${CURSES_LIBRARIES} )
