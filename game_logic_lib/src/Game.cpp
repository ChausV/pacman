#include "Game.h"


#include <ncurses.h>



#include <iostream>

Game::Game() :  maze(),
                pacman(maze.getPacmanStart().first, maze.getPacmanStart().second),
                ghost(maze.getGhostSpawn().first, maze.getGhostSpawn().second, 'd', ' '),
                ghost2(maze.getGhostSpawn().first, maze.getGhostSpawn().second, 'd', 'B'),
                ghost3(maze.getGhostSpawn().first, maze.getGhostSpawn().second, 'd', 'S'),
                ghost4(maze.getGhostSpawn().first, maze.getGhostSpawn().second, 'd', 'I'),
                ghosts({&ghost, &ghost2, &ghost3, &ghost4}),
                score(0), lives(5),
                mld(nullptr), main_loop_state(true)
{
    std::cout << "Constructor Game" << std::endl;
}

Game::~Game()
{
    delete mld;
    std::cout << "Destructor Game" << std::endl;
}


std::pair<int, int> Game::getGameFieldSize() const {
    const std::pair<int, int> size(maze.getFieldHeight(), maze.getFieldWidth());
    return size;
}
int Game::getGameScore() const {
    return score;
}
char ** Game::getGameField() const {
    return maze.getField();
}
bool Game::getMainLoopState() const {
    return main_loop_state;
}
unsigned Game::getFramesCounter() const {
    return mld->frames_counter;
}
float Game::getGameTime() const {
    return mld->game_time;
}
int Game::getGameLives() const {
    return lives;
}


void Game::pacmanLeft() {
    pacman.setNextDirection('l');
}
void Game::pacmanRight() {
    pacman.setNextDirection('r');
}
void Game::pacmanUp() {
    pacman.setNextDirection('u');
}
void Game::pacmanDown() {
    pacman.setNextDirection('d');
}


void Game::eatDot()
{
    score += 10;
    maze.decrementDotNumber();
    if (maze.getDotNumber() == 0)
    {
        changeLevel();
    }
}

void Game::eatCookie()
{
    score += 50;
    maze.decrementDotNumber();

    if (maze.getDotNumber() == 0)
    {
        changeLevel();
    }
    else
    {
        for(auto g : ghosts)
        {
            g->setScareCount(20);
            g->oppositeDirection();
        }
    }
}

void Game::pacmanToStart()
{
    pacman.move(maze, maze.getPacmanStart().first, maze.getPacmanStart().second);
    pacman.setNextDirection('l');
}

void Game::ghostToSpawn(Ghost * ghost)
{
    ghost->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
    ghost->restoreExitCounter();
    ghost->setScareCount(0);
    ghost->setCurrDirection('d');
}

void Game::scaredGhostToSpawn(Ghost * ghost)
{
    if (ghost->getStayOn() == '.')
    {
        eatDot();
    }
    if (ghost->getStayOn() == 'o')
    {
        eatCookie();
    }

    ghost->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
    ghost->restoreExitCounter();
    ghost->setScareCount(0);
    ghost->setCurrDirection('d');

    // crutch from pacman blinking here
    (maze.getField())[pacman.getY()][pacman.getX()] = 'P';  // ugly things )
}

void Game::collision()
{
    if(!--lives)
        main_loop_state = false;

    pacmanToStart();

    for(auto g : ghosts)
    {
        ghostToSpawn(g);
    }
}

void Game::changeLevel()
{
    maze.reloadMap();

    // move() is bad here in case of other map
    pacman.setY(maze.getPacmanStart().first);
    pacman.setX(maze.getPacmanStart().second);
    pacman.setNextDirection('l');

    for(auto g : ghosts)
    {
        g->setY(maze.getGhostSpawn().first);
        g->setX(maze.getGhostSpawn().second);
        g->restoreExitCounter();
        g->setScareCount(0);
        g->setCurrDirection('d');
    }
}

void Game::processStep()
{
    char where = pacman.moveStep(maze);
    if (where == '.')
    {
        eatDot();
    }
    else if (where == 'o')
    {
        eatCookie();
    }
    else if (where == 'B' || where == 'S' || where == 'I' || where == 'C')
    {
        collision();
    }
    else if (where == 'G')
    {
        score += 200;
        for(auto g : ghosts)
        {
            if (pacman.getX() == g->getX() && pacman.getY() == g->getY())
            {
                scaredGhostToSpawn(g);
            }
        }
    }

    for(auto g : ghosts)
    {
        if (g->getScareCount() && mld->frames_counter % 2)
            continue;
        where = g->moveStep(maze, pacman);
        if (where == 'P')
        {
            if (g->getScareCount())
            {
                scaredGhostToSpawn(g);
            }
            else
            {
                collision();
            }
        }
    }

    ++mld->frames_counter;
}

bool Game::mainLoopProcessing(int input)
{
    if (!mld)
    {
        mld = new MainLoopData;
    }

    if (input != -1)
    {
        mld->input = input;
    }

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    float diff = std::chrono::duration_cast<std::chrono::duration<float>>(now - mld->start).count();

    if (diff > mld->game_time)
    {
        switch(mld->input)
        {
            case 'q':
                main_loop_state = false;
                break;
            case 'p':
                if (mld->pause)
                    mld->pause = false;
                else
                    mld->pause = true;
                break;
        }
        if (!mld->pause)
        {
            switch(mld->input)
            {
                case 260:
                    pacmanLeft();
                    break;
                case 261:
                    pacmanRight();
                    break;
                case 259:
                    pacmanUp();
                    break;
                case 258:
                    pacmanDown();
                    break;
            }
            processStep();
        }
        mld->input = -1;

        mld->game_time += 0.25f;

        return true;
    }
    return false;
}
