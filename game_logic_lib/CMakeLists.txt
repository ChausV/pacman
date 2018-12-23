cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o0 -g -Wall -Wextra -Werror")

set(LOGIC_LIBRARY_NAME "logic")
set(LOGIC_LIBRARY_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Maze.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/AMazeHabitant.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Pacman.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/AGhost.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Blinky.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Speedy.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Inky.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Clyde.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${LOGIC_LIBRARY_NAME} SHARED ${LOGIC_LIBRARY_SRC})
