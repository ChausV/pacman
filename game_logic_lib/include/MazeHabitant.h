#ifndef MAZE_HABITANT_H
#define MAZE_HABITANT_H

#include "Maze.h"
class Maze;

class MazeHabitant
{
public:
    MazeHabitant();
    virtual ~MazeHabitant() = default;
    
    int getY() const;
    int getX() const;
    char getCurrDirection() const;

    void setY(int y);
    void setX(int x);
    void setCurrDirection(char c);

    virtual char move(Maze & m, int y, int x) = 0;
    // virtual char moveStep(Maze & m);

protected:
    int y;
    int x;
    char currentDirection;
};

#endif // MAZE_HABITANT_H
