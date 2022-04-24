cmake_minimum_required(VERSION 3.12)
project(zad4)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main PUBLIC
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        winMM.Lib)
