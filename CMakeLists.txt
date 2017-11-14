cmake_minimum_required(VERSION 3.8)
file(GLOB_RECURSE SOURCES glad/*.c src/*.cpp)


add_library(GLWrapper SHARED ${SOURCES})

#set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
#dd_subdirectory(assimp)
#find_package(assimp REQUIRED)
#target_link_libraries(GLWrapper assimp)
#target_include_directories(GLWrapper PRIVATE assimp/include)

target_include_directories(GLWrapper PRIVATE include)
target_include_directories(GLWrapper PRIVATE glad/include)


set(GLWRAPPER_LIBRARY "${CMAKE_CURRENT_BINARY_DIR}/libGLWrapper.dll" CACHE INTERNAL "")
set(GLWRAPPER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/glad/include" CACHE INTERNAL "")

#install (TARGETS GLWrapper
#ARCHIVE DESTINATION lib
#LIBRARY DESTINATION lib
#RUNTIME DESTINATION bin)