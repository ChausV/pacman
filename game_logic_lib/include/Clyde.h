#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"

class Clyde : public Ghost
{
public:
    Clyde(int y, int x, char currDir = 'd', char stayOn = ' ', char name = 'C');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);
    char newDirection_2(const Maze & m, const Pacman & p);
};

#endif // CLYDE_H
