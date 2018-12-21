#include "Speedy.h"

Speedy::Speedy(int y, int x, char currDir, char stayOn)
     : Ghost(y, x, currDir, stayOn, 'S', 10, 10)
{}

char Speedy::moveStep(Maze & m, Pacman & p)
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

char Speedy::newDirection(const Maze & m, const Pacman & p)
{
    char ** f = m.getField();
    const int px = p.getX();
    const int py = p.getY();

    if (currentDirection == 'l' || currentDirection == 'r')
    {
        if (py < y && f[y - 1][x] != 'X' && f[y - 1][x] != '_')
            return 'u';
        if (py < y && f[y + 1][x] != 'X' && f[y + 1][x] != '_')
            return 'd';
        else if (py > y && f[y + 1][x] != 'X' && f[y + 1][x] != '_')
            return 'd';
        else if (py > y && f[y - 1][x] != 'X' && f[y - 1][x] != '_')
            return 'u';
        else
            return (currentDirection == 'l') ? 'r' : 'l';
    }
    else
    {
        if (px < x && f[y][x - 1] != 'X' && f[y][x - 1] != '_')
            return 'l';
        else if (px < x && f[y][x + 1] != 'X' && f[y][x + 1] != '_')
            return 'r';
        else if (px > x && f[y][x + 1] != 'X' && f[y][x + 1] != '_')
            return 'r';
        else if (px > x && f[y][x - 1] != 'X' && f[y][x - 1] != '_')
            return 'l';
        else
            return (currentDirection == 'u') ? 'd' : 'u';
    }
}
