#include "MazeHabitant.h"

MazeHabitant::MazeHabitant() :  currentDirection('l'), nextDirection('l')
{}

char MazeHabitant::getCurrDirection() const { return currentDirection; }
char MazeHabitant::getNextDirection() const { return nextDirection; }
int MazeHabitant::getY() const { return y; }
int MazeHabitant::getX() const { return x; }

void MazeHabitant::setY(int y) { this->y = y; }
void MazeHabitant::setX(int x) { this->x = x; }
void MazeHabitant::setCurrDirection(char c) { currentDirection = c; }
void MazeHabitant::setNextDirection(char c) { nextDirection = c; }
