cmake_minimum_required(VERSION 3.13.2)
project(COMBO)

set(CMAKE_MODULE_PATH ${COMBO_SOURCE_DIR}/cmake)



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
    include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})
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

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/libs)
#include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/resources)
#include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/tools)

#Source files
set(SOURCE_FILES

)

add_executable(Combo ${SOURCE_FILES})

target_link_libraries(Combo
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE__LIBRARIES}
    ${ASSIMP_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLM_LIBRARIES}
)

#ImGuI ImGuizmo OPENAL bullet reactphysics3d