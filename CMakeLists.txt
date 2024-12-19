cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS} -pthread")

project(SnakeGame)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/score_manager.cpp src/livesManager.cpp src/state_manager.cpp)

if(APPLE)
    # macOS-specific setup
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    include_directories(/opt/local/include)
    link_directories(/opt/local/lib)

    find_library(SDL2_LIB SDL2 HINTS /opt/local/lib)
    find_library(SDL2_IMAGE_LIB SDL2_image HINTS /opt/local/lib)
    find_library(SDL2_TTF_LIB SDL2_ttf HINTS /opt/local/lib)
    
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB})
elseif(UNIX AND NOT APPLE)
# Linux-specific setup
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    pthread
)
endif()

include_directories(${SDL2_INCLUDE_DIRS} src)

#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
#target_link_libraries(SnakeGame ${SDL2_LIBRARIES})
