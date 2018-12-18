#include "Game.h"

#include <iostream>

Game::Game() : ghost(nullptr), ghost2(nullptr),ghost3(nullptr), ghost4(nullptr),
                maze(pacman), score(0), lives(5),
                mld(nullptr), main_loop_state(true)
{
    std::cout << "Constructor Game" << std::endl;
}

Game::~Game()
{
    delete mld;
    delete ghost;
    delete ghost2;
    delete ghost3;
    delete ghost4;
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

    // (maze.getField())[pacman.getY()][pacman.getX()] = ' ';
    if (ghost)
    {
        ghost->move(maze, 7, 12);
        ghost->setCurrDirection('d');
    }
    if (ghost2)
    {
        ghost2->move(maze, 7, 10);
        ghost2->setCurrDirection('d');
    }
    if (ghost3)
    {
        ghost3->move(maze, 7, 13);
        ghost3->setCurrDirection('d');
    }
    if (ghost4)
    {
        ghost4->move(maze, 7, 9);
        ghost4->setCurrDirection('d');
    }

    pacman.move(maze, 17, 11);
    pacman.setNextDirection('l');


    // (maze.getField())[ghost->getY()][ghost->getX()] = ' ';
}

void Game::processStep()
{
    // char where = maze.shiftHabitant(pacman);
    char where = pacman.moveStep(maze);
    if (where == '.')
    {
        score += 10;
    }
        if (where == 'o')
    {
        score += 50;
    }
    else if (where == 'B' || where == 'S' || where == 'I' || where == 'C')
    {
        collision();
    }

    if (ghost)
    {
        where = ghost->moveStep(maze, pacman);
        if (where == 'P')
        {
            collision();
        }
    }
    if (ghost2)
    {
        where = ghost2->moveStep(maze, pacman);
        if (where == 'P')
        {
            collision();
        }
    }
    if (ghost3)
    {
        where = ghost3->moveStep(maze, pacman);
        if (where == 'P')
        {
            collision();
        }
    }
    if (ghost4)
    {
        where = ghost4->moveStep(maze, pacman);
        if (where == 'P')
        {
            collision();
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

    if (!ghost && mld->frames_counter > 10)
    {
        ghost = new Blinky;
        ghost->setX(11);
        ghost->setY(7);
        ghost->setCurrDirection('u');
        ghost->setStayOn((maze.getField())[7][11]);
    }
    if (!ghost2 && mld->frames_counter > 20)
    {
        ghost2 = new Speedy;
        ghost2->setX(11);
        ghost2->setY(7);
        ghost2->setCurrDirection('u');
        ghost2->setStayOn((maze.getField())[7][11]);
    }
    if (!ghost3 && mld->frames_counter > 30)
    {
        ghost3 = new Inky;
        ghost3->setX(11);
        ghost3->setY(7);
        ghost3->setCurrDirection('u');
        ghost3->setStayOn((maze.getField())[7][11]);
    }
    if (!ghost4 && mld->frames_counter > 40)
    {
        ghost4 = new Clyde;
        ghost4->setX(11);
        ghost4->setY(7);
        ghost4->setCurrDirection('u');
        ghost4->setStayOn((maze.getField())[7][11]);
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

        mld->game_time += 0.2f;

        return true;
    }
    return false;
}
