cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "pacman")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o0 -g -Wall -Wextra -Werror")

add_subdirectory("game_logic_lib")
add_subdirectory("user_interface_lib")

set(LIBRARIES "logic" "uincurses")

include_directories(
#	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/game_logic_lib/include
	${CMAKE_CURRENT_SOURCE_DIR}/user_interface_lib/include
)

set(EXECUTABLE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/pacman_main.cpp
)

add_executable(${PROJECT_NAME} ${EXECUTABLE_SRC})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
