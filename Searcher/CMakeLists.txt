cmake_minimum_required (VERSION 3.23)

project(SearcherLib)
set(CMAKE_CXX_STANDARD 23)

add_library(SearcherLib STATIC InFileSearcher.cpp InFileSearcher.h)