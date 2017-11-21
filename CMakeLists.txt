cmake_minimum_required(VERSION 3.8)
file(GLOB_RECURSE SOURCES glad/*.c src/*.cpp)
file(GLOB_RECURSE INCLUDES include/*.h)

set(CMAKE_INSTALL_PREFIX "E:/msys64/mingw64" CACHE INTERNAL "") # For now, later remove this

find_package(assimp REQUIRED)
#find_package(glm REQUIRED)
#find_package(jsoncpp REQUIRED)

add_library(tools3d SHARED ${SOURCES})

target_include_directories(tools3d PRIVATE include)
target_include_directories(tools3d PRIVATE glad/include)

# ASSIMP
target_include_directories(tools3d PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_link_libraries(tools3d ${ASSIMP_LIBRARIES})

# GLM - For later, I don't need it right now.
#target_include_directories(tools3d PUBLIC ${GLM_INCLUDE_DIRS})
#target_link_libraries(tools3d ${GLM_LIBRARY})

# JSONCPP - for parsing the scene file.
#target_include_directories(tools3d PRIVATE ${JSONCPP_INCLUDE_DIRS})
#target_link_libraries(tools3d ${JSONCPP_LIBRARY})


install(TARGETS tools3d
RUNTIME DESTINATION bin
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib)
install(FILES ${INCLUDES} DESTINATION include/tools3d)
install(FILES "glad/include/glad/glad.h" DESTINATION include/tools3d/glad)
install(FILES "glad/include/KHR/khrplatform.h" DESTINATION include/tools3d/glad/KHR)