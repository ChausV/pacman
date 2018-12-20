#ifndef INKY_H
#define INKY_H

#include "Ghost.h"

class Inky : public Ghost
{
public:
    Inky(int y, int x, char currDir = 'd', char stayOn = ' ', char name = 'I');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);
    char newDirection_2(const Maze & m, const Pacman & p);
};

#endif // INKY_H
