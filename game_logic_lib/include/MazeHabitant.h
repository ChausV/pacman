#ifndef MAZE_HABITANT_H
#define MAZE_HABITANT_H

#include "Maze.h"
class Maze;

class MazeHabitant
{
public:
    MazeHabitant();
    ~MazeHabitant() = default;
    
    int getY() const;
    int getX() const;
    char getCurrDirection() const;
    char getNextDirection() const;

    void setY(int y);
    void setX(int x);
    void setCurrDirection(char c);
    void setNextDirection(char c);

    char move(Maze & m, int y, int x);
    char moveStep(Maze & m);

private:
    int y;
    int x;
    char currentDirection;
    char nextDirection;
};

#endif // MAZE_HABITANT_H
