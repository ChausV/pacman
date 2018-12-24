#ifndef GAME_H
#define GAME_H

#include <vector>

#include "IGame.h"
#include "Maze.h"
#include "Pacman.h"
#include "Blinky.h"
#include "Speedy.h"
#include "Inky.h"
#include "Clyde.h"
#include "MainLoopData.h"

class Game : public IGame
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
    int getGameLives() const;
    int getGameLevel() const;

    bool mainLoopProcessing(int input);

private:

    Maze maze;

    Pacman pacman;
    Blinky ghost;
    Speedy ghost2;
    Inky ghost3;
    Clyde ghost4;

    std::vector<AGhost*> ghosts;

    int score;
    int lives;
    int level;

    MainLoopData * mld;

    bool main_loop_state;

    void pacmanLeft();
    void pacmanRight();
    void pacmanUp();
    void pacmanDown();

    void eatDot();
    void eatCookie();

    void pacmanToStart();
    void ghostToSpawn(AGhost * ghost);
    void scaredGhostToSpawn(AGhost * ghost);

    void processStep();
    void collision();
    void changeLevel();
};

#endif // GAME_H
