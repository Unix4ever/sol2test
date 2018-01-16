cmake_minimum_required(VERSION 3.1)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

project(sol2test)

include(conanbuildinfo.cmake)
conan_basic_setup()

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
  add_definitions(-DWIN32)
else(WIN32)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_FLAGS "-fPIC -O0 ${CMAKE_CXX_FLAGS}")
  set(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif(WIN32)


include_directories(src)

add_executable(runner src/main.cpp)
add_library(common SHARED src/common.cpp src/EventDispatcher.cpp src/base.cpp)
add_library(library SHARED src/library.cpp)

target_link_libraries(common ${CONAN_LIBS_LUAJIT-ROCKS})

target_link_libraries(library ${CONAN_LIBS_LUAJIT-ROCKS} ${CONAN_LIBS} common)

target_link_libraries(runner common library ${CONAN_LIBS_LUAJIT-ROCKS})

if(WIN32)
  set_target_properties(runner PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif(WIN32)
