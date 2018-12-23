#ifndef CLYDE_H
#define CLYDE_H

#include "AGhost.h"

class Clyde : public AGhost
{
public:
    Clyde(int y, int x, char currDir = 'd', char stayOn = ' ');

    virtual char moveStep(Maze & m, Pacman & p);

protected:

    virtual char newDirection(const Maze & m, const Pacman & p);
    char newDirection_2(const Maze & m, const Pacman & p);
};

#endif // CLYDE_H
