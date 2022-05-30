cmake_minimum_required(VERSION 3.21)
project(zad2)

set(CMAKE_CXX_STANDARD 17)

add_executable(zad2 main.cpp sender.cpp sender.h receiver.cpp receiver.h global_consts.h utility.h utility.cpp)
