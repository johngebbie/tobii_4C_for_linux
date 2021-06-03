cmake_minimum_required(VERSION 3.13)
project(streamer)

set(CMAKE_CXX_STANDARD 14)
add_executable(streamer streamer.cpp)
target_link_libraries(streamer /usr/lib/tobii/libtobii_stream_engine.so)
target_link_libraries(streamer pthread)

