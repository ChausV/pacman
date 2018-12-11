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
	char where = maze.moveHabitant(pacman, pacman.getY(), pacman.getX() - 1);
	if (where == '.') { ++score; }
}

void Game::pacmanRight()
{
	char where = maze.moveHabitant(pacman, pacman.getY(), pacman.getX() + 1);
	if (where == '.') { ++score; }
}

void Game::pacmanUp()
{
	char where = maze.moveHabitant(pacman, pacman.getY() - 1, pacman.getX());
	if (where == '.') { ++score; }
}

void Game::pacmanDown()
{
	char where = maze.moveHabitant(pacman, pacman.getY() + 1, pacman.getX());
	if (where == '.') { ++score; }
}
