cmake_minimum_required(VERSION 3.4.1)

add_library(pipe-jni
            SHARED
            src/main/jni/pipe-jni.c)

target_link_libraries(pipe-jni)