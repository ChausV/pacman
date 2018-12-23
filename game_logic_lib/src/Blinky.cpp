#include "Blinky.h"

Blinky::Blinky(int y, int x, char currDir, char stayOn)
     : AGhost(y, x, currDir, stayOn, 'B', 1, 1)
{}

char Blinky::moveStep(Maze & m, Pacman & p)
{
    char where = checkExitCounter(m);
    if (where != 'N')
        return where;

    if (scareCounter)
    {
        --scareCounter;
        currentDirection = scareDirection(m);
        return makeCurrDirStep(m);
    }

    where = makeCurrDirStep(m);
    if (where != 'N')
    {
        return where;
    }
    currentDirection = newDirection(m, p);
    return makeCurrDirStep(m);
}

char Blinky::newDirection(const Maze & m, const Pacman & p)
{
    char ** f = m.getField();
    const int px = p.getX();
    const int py = p.getY();

    if (currentDirection == 'l' || currentDirection == 'r')
    {
        if (py < y && f[y - 1][x] != 'X' && f[y - 1][x] != '_')
            return 'u';
        else if (py > y && f[y + 1][x] != 'X' && f[y + 1][x] != '_')
            return 'd';
        else
            return (currentDirection == 'l') ? 'r' : 'l';
    }
    else
    {
        if (px < x && f[y][x - 1] != 'X' && f[y][x - 1] != '_')
            return 'l';
        else if (px > x && f[y][x + 1] != 'X' && f[y][x + 1] != '_')
            return 'r';
        else
            return (currentDirection == 'u') ? 'd' : 'u';
    }
}
