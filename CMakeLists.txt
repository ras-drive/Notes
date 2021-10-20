cmake_minimum_required(VERSION 3.20)
project(Notes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  "-pthread")

# target_link_libraries(-pthread)


add_executable(Notes lib/main.cpp lib/notes.h lib/csv.h)
