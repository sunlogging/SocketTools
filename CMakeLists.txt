cmake_minimum_required(VERSION 3.12)

project(main)

add_executable(main main.cpp)

add_library(curl STATIC IMPORTED)
set_target_properties(curl PROPERTIES IMPORTED_LOCATION libs/libcurl.a)

target_link_libraries(main curl)