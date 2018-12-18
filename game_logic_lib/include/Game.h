#ifndef GAME_H
#define GAME_H

#include <utility>

#include "Maze.h"
#include "MazeHabitant.h"
#include "Pacman.h"
#include "Ghost.h"
#include "MainLoopData.h"

class Game
{
public:
    Game();
    ~Game();

    std::pair<int, int> getGameFieldSize() const;
    char ** getGameField() const;

    int getGameScore() const;
    bool getMainLoopState() const;
    unsigned getFramesCounter() const;
    float getGameTime() const;


    void pacmanLeft();
    void pacmanRight();
    void pacmanUp();
    void pacmanDown();

    void processStep();

    bool mainLoopProcessing(int input);


private:

    Pacman pacman;
    Ghost * ghost;

    Maze maze;

    int score;

    MainLoopData * mld;

    bool main_loop_state;

};

#endif // GAME_H


/*

XXXXXXXXXXXXXXXXXXXXXXXXXXXX
X............XX............X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X..........................X
X.XXXX.XX.XXXXXXXX.XX.XXXX.X
X.XXXX.XX.XXXXXXXX.XX.XXXX.X
X......XX....XX....XX......X
XXXXXX.XXXXX.XX.XXXXX.XXXXXX
     X.XXXXX.XX.XXXXX.X     
     X.XX          XX.X     
     X.XX XXXXXXXX XX.X     
XXXXXX.XX X      X XX.XXXXXX
      .   X      X   .      
XXXXXX.XX X      X XX.XXXXXX
     X.XX XXXXXXXX XX.X     
     X.XX          XX.X     
     X.XX XXXXXXXX XX.X     
XXXXXX.XX XXXXXXXX XX.XXXXXX
X............XX............X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X...XX................XX...X
XXX.XX.XX.XXXXXXXX.XX.XX.XXX
XXX.XX.XX.XXXXXXXX.XX.XX.XXX
X......XX....XX....XX......X
X.XXXXXXXXXX.XX.XXXXXXXXXX.X
X.XXXXXXXXXX.XX.XXXXXXXXXX.X
X..........................X
XXXXXXXXXXXXXXXXXXXXXXXXXXXX




XXXXXXXXXXXXXXXXXXXXXXXXXXXX
X............XX............X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X..........................X
X.XXXX.XX.XXXXXXXX.XX.XXXX.X
X......XX....XX....XX......X
XXXXXX.XXXXX.XX.XXXXX.XXXXXX
     X.XX          XX.X     
     X.XX XXXXXXXX XX.X     
XXXXXX.XX X      X XX.XXXXXX
      .   X      X   .      
XXXXXX.XX X      X XX.XXXXXX
     X.XX XXXXXXXX XX.X     
     X.XX          XX.X     
XXXXXX.XX XXXXXXXX XX.XXXXXX
X............XX............X
X.XXXX.XXXXX.XX.XXXXX.XXXX.X
X...XX................XX...X
XXX.XX.XX.XXXXXXXX.XX.XX.XXX
X......XX....XX....XX......X
X.XXXXXXXXXX.XX.XXXXXXXXXX.X
X..........................X
XXXXXXXXXXXXXXXXXXXXXXXXXXXX



*/