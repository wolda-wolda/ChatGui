cmake_minimum_required(VERSION 3.19)
project(ChatGui C)

set(CMAKE_C_STANDARD 11)
link_libraries(ws2_32 wsock32)

set(SOURCE_FILES client.c gui.c)
add_executable(ChatGui ${SOURCE_FILES})
