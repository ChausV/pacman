#include "AMazeHabitant.h"

AMazeHabitant::AMazeHabitant(int y, int x, char currDir)
	: y(y), x(x), currentDirection(currDir)
{}

char AMazeHabitant::getCurrDirection() const { return currentDirection; }
int AMazeHabitant::getY() const { return y; }
int AMazeHabitant::getX() const { return x; }

void AMazeHabitant::setY(int y) { this->y = y; }
void AMazeHabitant::setX(int x) { this->x = x; }
void AMazeHabitant::setCurrDirection(char c) { currentDirection = c; }
