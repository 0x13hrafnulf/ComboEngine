cmake_minimum_required(VERSION 3.3)
project(COMBO)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/"; 
"${CMAKE_SOURCE_DIR}/libs/") 
#include(${CMAKE_SOURCE_DIR}/libs/CMakeLists.txt)


if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(SYSTEM ${OPENGL_INCLUDE_DIRS})
endif(OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(SYSTEM ${SDL2_INCLUDE_DIR})
endif(SDL2_FOUND)


find_package(SDL2_image REQUIRED SDL2_image>=2.0.0)
if(SDL2_IMAGE_FOUND)
    include_directories(SYSTEM ${SDL2_IMAGE_INCLUDE_DIRS})
endif(SDL2_IMAGE_FOUND)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(SYSTEM ${GLM_INCLUDE_DIRS})
endif(GLM_FOUND)

find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
    include_directories(SYSTEM ${ASSIMP_INCLUDE_DIRS})
endif(ASSIMP_FOUND)


#include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/resources)
#include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/tools)

#Source files

#file(GLOB_RECURSE headers ${Combo_SOURCE_DIR}/src/*.h)

#file(GLOB_RECURSE sources ${Combo_SOURCE_DIR}/src/*.cpp)
set(source_files 
src/main.cpp
src/Combo.h
src/Combo/Engine.cpp
src/Combo/LogManager.cpp
)
 
add_executable(Combo ${source_files})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/spdlog/include/
    )

target_link_libraries(Combo
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE__LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLM_LIBRARIES}
)

#ImGuI ImGuizmo OPENAL bullet reactphysics3d