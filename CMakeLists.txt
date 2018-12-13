cmake_minimum_required(VERSION 3.12)
project(dwm_6_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dwm_6_1
        config.h
        drw.c
        drw.h
        dwm.c
        transient.c
        util.c
        util.h)
