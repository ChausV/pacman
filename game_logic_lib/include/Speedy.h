#ifndef SPEEDY_H
#define SPEEDY_H

#include "Ghost.h"

class Speedy : public Ghost
{
public:
    Speedy();

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);

};

#endif // SPEEDY_H
