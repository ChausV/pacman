#include "Game.h"

#include <iostream>

Game::Game() : maze(pacman), score(0), mld(nullptr), main_loop_state(true)
{
    std::cout << "Constructor Game" << std::endl;
}

Game::~Game()
{
    delete mld;
    std::cout << "Destructor Game" << std::endl;
}

std::pair<int, int> Game::getGameFieldSize() const
{
    const std::pair<int, int> size(maze.getFieldHeight(), maze.getFieldWidth());
    return size;
}

int Game::getGameScore() const
{
    return score;
}

char ** Game::getGameField() const
{
    return maze.getField();
}

bool Game::getMainLoopState() const
{
    return main_loop_state;
}

unsigned Game::getFramesCounter() const
{
    return mld->frames_counter;
}

float Game::getGameTime() const
{
    return mld->game_time;
}

void Game::pacmanLeft()
{
    pacman.setNextDirection('l');
    // char where = maze.moveHabitant(pacman, pacman.getY(), pacman.getX() - 1);
    // if (where == '.') { ++score; }
}

void Game::pacmanRight()
{
    pacman.setNextDirection('r');
    // char where = maze.moveHabitant(pacman, pacman.getY(), pacman.getX() + 1);
    // if (where == '.') { ++score; }
}

void Game::pacmanUp()
{
    pacman.setNextDirection('u');
    // char where = maze.moveHabitant(pacman, pacman.getY() - 1, pacman.getX());
    // if (where == '.') { ++score; }
}

void Game::pacmanDown()
{
    pacman.setNextDirection('d');
    // char where = maze.moveHabitant(pacman, pacman.getY() + 1, pacman.getX());
    // if (where == '.') { ++score; }
}

void Game::processStep()
{
    char where = maze.shiftHabitant(pacman);
    if (where == '.') { ++score; }
}

bool Game::mainLoopProcessing(int input)
{
    if (!mld)
    {
        mld = new MainLoopData();
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
            case 260:
                if (!mld->pause)
                    pacmanLeft();
                break;
            case 261:
                if (!mld->pause)
                    pacmanRight();
                break;
            case 259:
                if (!mld->pause)
                    pacmanUp();
                break;
            case 258:
                if (!mld->pause)
                    pacmanDown();
                break;
        }
        mld->input = -1;
        if (!mld->pause)
        {
            processStep();
            ++mld->frames_counter;
        }

        mld->game_time += 0.2f;

        return true;
    }
    return false;
}
