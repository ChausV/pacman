#include "MazeHabitant.h"

MazeHabitant::MazeHabitant() :  currentDirection('l')
{}

char MazeHabitant::getCurrDirection() const { return currentDirection; }
int MazeHabitant::getY() const { return y; }
int MazeHabitant::getX() const { return x; }

void MazeHabitant::setY(int y) { this->y = y; }
void MazeHabitant::setX(int x) { this->x = x; }
void MazeHabitant::setCurrDirection(char c) { currentDirection = c; }
