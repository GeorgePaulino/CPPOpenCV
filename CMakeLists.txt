cmake_minimum_required(VERSION 3.2)

project(TankGame)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE TankGame_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.hpp" "src/*.cpp" "src/**/*.h" "src/**/*.hpp" "src/**/*.cpp")

find_package(OpenCV REQUIRED)
find_package(GTK2 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

add_executable(TankGame ${TankGame_SRC})

target_link_libraries(TankGame ${OpenCV_LIBS})
target_link_libraries(TankGame ${GTK2_LIBRARIES})
target_link_libraries(TankGame ${SDL2_LIBRARIES})
target_link_libraries(TankGame ${SDL_IMAGE_LIBRARIES})
target_link_libraries(TankGame SDL2_image)