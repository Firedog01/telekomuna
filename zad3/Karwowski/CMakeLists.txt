cmake_minimum_required(VERSION 3.12)

project(telekom_zad3)

include_directories(include)

set(SOURCE_FILES
	src/ReaderWriter.cpp
        src/main.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ncurses -static)
