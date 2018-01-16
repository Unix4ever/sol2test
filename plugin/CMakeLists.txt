
include_directories(./include)
include_directories(${CMAKE_SOURCE_DIR}/main/include)
include_directories(${CMAKE_SOURCE_DIR}/include_sol2)
include_directories(${CMAKE_SOURCE_DIR}/common/include)

add_library("library" SHARED src/library.cpp)

target_link_libraries(library common ${CONAN_LIBS_OGRE} ${CONAN_LIBS_LUAJIT-ROCKS} ${LIBS})
