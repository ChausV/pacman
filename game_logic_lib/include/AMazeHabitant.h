#ifndef A_MAZE_HABITANT_H
#define A_MAZE_HABITANT_H

#include "Maze.h"
class Maze;

class AMazeHabitant
{
public:
    AMazeHabitant(int y, int x, char currDir = 'l');
    virtual ~AMazeHabitant() = default;
    
    int getY() const;
    int getX() const;
    char getCurrDirection() const;

    void setY(int y);
    void setX(int x);
    void setCurrDirection(char c);

    virtual char move(Maze & m, int y, int x) = 0;

protected:
    int y;
    int x;
    char currentDirection;
};

#endif // A_MAZE_HABITANT_H
