cmake_minimum_required (VERSION 3.23)

project(SimpleTimerLib)
set(CMAKE_CXX_STANDARD 23)

add_library(SimpleTimerLib STATIC SimpleTimer.cpp SimpleTimer.h)