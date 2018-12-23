#ifndef BLINKY_H
#define BLINKY_H

#include "AGhost.h"

class Blinky : public AGhost
{
public:
    Blinky(int y, int x, char currDir = 'd', char stayOn = ' ');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);

};

#endif // BLINKY_H
