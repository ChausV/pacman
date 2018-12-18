#ifndef MAZE_H
#define MAZE_H

#include "MazeHabitant.h"
class MazeHabitant;

class Maze
{
public:
    Maze(MazeHabitant & pacman);
    ~Maze();

    int getFieldHeight() const;
    int getFieldWidth() const;
    char ** getField() const;

    // parameters: move whom, move where
    // char moveHabitant(MazeHabitant & h, int y, int x);
    // char shiftHabitant(MazeHabitant & h);

private:

    int field_h;
    int field_w;
    char ** field;

};

#endif // MAZE_H
