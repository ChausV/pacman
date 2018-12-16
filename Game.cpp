#include "Game.h"

#include <iostream>

Game::Game() : maze(Maze(pacman)), score(0)
{
    std::cout << "Constructor Game" << std::endl;
}

Game::~Game()
{
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
