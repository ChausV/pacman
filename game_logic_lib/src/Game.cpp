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


void Game::collision()
{
    if(!--lives)
        main_loop_state = false;

    for(auto g : ghosts)
    {
        g->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
        g->restoreExitCounter();
    }

    pacman.move(maze, maze.getPacmanStart().first, maze.getPacmanStart().second);
    pacman.setNextDirection('l');
}

void Game::processStep()
{
    char where = pacman.moveStep(maze);
    if (where == '.')
    {
        score += 10;
        maze.decrementDotNumber();

            mvprintw(40, 5, "dots: %d", maze.getDotNumber());
            refresh();

        if (maze.getDotNumber() == 0)
        {
            maze.reloadMap();
            for(auto g : ghosts)
            {
                g->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
                g->restoreExitCounter();
                g->setScareCount(0);
                g->setCurrDirection('d');
            }
            int xPr = pacman.getX();
            int yPr = pacman.getY();

            pacman.move(maze, maze.getPacmanStart().first, maze.getPacmanStart().second);
            pacman.setNextDirection('l');

            // one more crutch
            (maze.getField())[yPr][xPr] = '.';
        }
    }
    else if (where == 'o')
    {
        score += 50;
        maze.decrementDotNumber();

        if (maze.getDotNumber() == 0)
        {
            maze.reloadMap();
            for(auto g : ghosts)
            {
                g->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
                g->restoreExitCounter();
                g->setScareCount(0);
                g->setCurrDirection('d');
            }
            int xPr = pacman.getX();
            int yPr = pacman.getY();

            pacman.move(maze, maze.getPacmanStart().first, maze.getPacmanStart().second);
            pacman.setNextDirection('l');

            // one more crutch
            (maze.getField())[yPr][xPr] = 'o';
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
                g->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
                g->restoreExitCounter();
                g->setScareCount(0);
            }
        }
        // crutch from pacman blinking here
        (maze.getField())[pacman.getY()][pacman.getX()] = 'P';  // ugly things )
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
                g->move(maze, maze.getGhostSpawn().first, maze.getGhostSpawn().second);
                g->restoreExitCounter();
                g->setScareCount(0);
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
