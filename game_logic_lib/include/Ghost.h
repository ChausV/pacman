#ifndef GHOST_H
#define GHOST_H

#include "MazeHabitant.h"
#include "Pacman.h"

class Ghost : public MazeHabitant
{
public:
    // Ghost();

    char getStayOn() const;
    void setStayOn(char c);

    virtual char move(Maze & m, int y, int x);
    virtual char moveStep(Maze & m, Pacman & p);

    char newDirection(const Maze & m, const Pacman & p);

private:
    char stayOn;

    char tryToMove(Maze & m);
};

#endif // GHOST_H
