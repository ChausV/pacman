#ifndef SPEEDY_H
#define SPEEDY_H

#include "AGhost.h"

class Speedy : public AGhost
{
public:
    Speedy(int y, int x, char currDir = 'd', char stayOn = ' ');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);

};

#endif // SPEEDY_H
