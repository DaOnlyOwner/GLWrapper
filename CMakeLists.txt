cmake_minimum_required(VERSION 3.8)
file(GLOB_RECURSE SOURCES glad/*.c src/*.cpp)
file(GLOB_RECURSE INCLUDES glad/*.h include/*.h)

set(CMAKE_INSTALL_PREFIX "E:/msys64/mingw64" CACHE INTERNAL "") # For now, later remove this

find_package(assimp REQUIRED)
find_package(glm REQUIRED)

add_library(GLWrapper SHARED ${SOURCES})

target_include_directories(GLWrapper PRIVATE include)
target_include_directories(GLWrapper PRIVATE glad/include)

# ASSIMP
target_include_directories(GLWrapper PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_link_libraries(GLWrapper ${ASSIMP_LIBRARIES})

# GLM - For later, I don't need it right now.
target_include_directories(GLWrapper PUBLIC ${GLM_INCLUDE_DIRS})
target_link_libraries(GLWrapper ${GLM_LIBRARY})


install(TARGETS GLWrapper
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/GLWrapper)