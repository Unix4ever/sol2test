cmake_minimum_required(VERSION 3.1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

project(sol2test)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

add_subdirectory("main")
add_subdirectory("common")
add_subdirectory("plugin")
