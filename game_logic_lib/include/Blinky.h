#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"

class Blinky : public Ghost
{
public:
    Blinky(int y, int x, char currDir = 'd', char stayOn = ' ', char name = 'B');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);

};

#endif // BLINKY_H
