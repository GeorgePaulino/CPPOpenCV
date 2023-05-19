cmake_minimum_required(VERSION 3.2)

project( TankGame )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--dynamic-linker=/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2")


file( GLOB TankGame_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.hpp" "src/*.cpp" )

find_package( OpenCV REQUIRED )
find_package( GTK2 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( TankGame ${TankGame_SRC} )

target_link_libraries( TankGame ${OpenCV_LIBS} )
target_link_libraries( TankGame ${GTK2_LIBRARIES} )

