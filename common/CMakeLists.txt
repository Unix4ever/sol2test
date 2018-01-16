include_directories(${CONAN_INCLUDE_DIRS})
include_directories(./include)
include_directories(${CMAKE_SOURCE_DIR}/include_sol2)

add_library("common" SHARED src/common.cpp src/EventDispatcher.cpp)
target_link_libraries(common ${CONAN_LIBS_LUAJIT-ROCKS})
