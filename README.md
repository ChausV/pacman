#### Pacman-like game.
Game requires ncurses library.  
Four enemies (ghosts) have different but not canonical behavior.  
So called "energizers" and ghosts scare mode are present in game.  
There are seven different levels and game speed increases a little bit on every level change.  
Program is separated into three parts: game logic, user interface and application itself.  
Game logic and user interface parts are placed into separate shared libraries.
Some descriptions of libraries interfaces can be found in [*'game_logic_lib/include/IGame.h'*](game_logic_lib/include/IGame.h) and
[*'user_interface_lib/include/IDisplay.h'*](user_interface_lib/include/IDisplay.h) files.  
Application itself places in main() function ([*'src/pacman_main.cpp'*](src/pacman_main.cpp) file).  
Permanent high scores table is available from the game menu.  
Enjoy the gameplay!
