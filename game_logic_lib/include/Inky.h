#ifndef INKY_H
#define INKY_H

#include "AGhost.h"

class Inky : public AGhost
{
public:
    Inky(int y, int x, char currDir = 'd', char stayOn = ' ');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);
    char newDirection_2(const Maze & m, const Pacman & p);
};

#endif // INKY_H
