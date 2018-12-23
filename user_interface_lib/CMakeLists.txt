cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o0 -g -Wall -Wextra -Werror")

set(UI_LIBRARY_NAME "uincurses")
set(UI_LIBRARY_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Display.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DisplayGame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainMenu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOverScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/HighScores.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_library(${UI_LIBRARY_NAME} SHARED ${UI_LIBRARY_SRC})
target_link_libraries(${UI_LIBRARY_NAME} ${CURSES_LIBRARIES})
