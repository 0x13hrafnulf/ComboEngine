cmake_minimum_required(VERSION 3.3)
project(App)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") 
include(cotire)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/Combo)


if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

add_executable(${PROJECT_NAME} src/Application/Application.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/Application/
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/libs/spdlog/include/
    ${CMAKE_SOURCE_DIR}/libs/imgui/
)

target_link_libraries(${PROJECT_NAME}
   Combo
)
cotire(App Combo)