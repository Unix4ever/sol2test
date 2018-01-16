cmake_minimum_required(VERSION 3.1)

include_directories(${CONAN_INCLUDE_DIRS})
include_directories(./include)
include_directories(${CMAKE_SOURCE_DIR}/common/include)
include_directories(${CMAKE_SOURCE_DIR}/plugin/include)
include_directories(${CMAKE_SOURCE_DIR}/include_sol2)

add_executable(runner src/main.cpp)

set_target_properties(runner PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

target_link_libraries(runner common library ${CONAN_LIBS_LUAJIT-ROCKS})
