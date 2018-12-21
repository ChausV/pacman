#include "Clyde.h"
#include "random"

Clyde::Clyde(int y, int x, char currDir, char stayOn)
     : Ghost(y, x, currDir, stayOn, 'C', 30, 30)
{}

char Clyde::moveStep(Maze & m, Pacman & p)
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    if (dis(gen) < 6)
    {
        currentDirection = newDirection(m, p);
    }
    else
    {
        where = makeCurrDirStep(m);
        if (where != 'N')
        {
            return where;
        }
        currentDirection = newDirection_2(m, p);
    }
    return makeCurrDirStep(m);
}

char Clyde::newDirection(const Maze & m, const Pacman & p)
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
        else if (currentDirection == 'l' &&
                (x == 0 || (f[y][x - 1] != 'X' && f[y][x - 1] != '_')))
            return 'l';
        else if (currentDirection == 'r' &&
                (x == (m.getFieldWidth() - 1) || (f[y][x + 1] != 'X' && f[y][x + 1] != '_')))
            return 'r';
        else
            return (currentDirection == 'l') ? 'r' : 'l';
    }
    else
    {
        if (px < x && f[y][x - 1] != 'X' && f[y][x - 1] != '_')
            return 'l';
        else if (px > x && f[y][x + 1] != 'X' && f[y][x + 1] != '_')
            return 'r';
        else if (currentDirection == 'u' &&
                (y == 0 || (f[y - 1][x] != 'X' && f[y - 1][x] != '_')))
            return 'u';
        else if (currentDirection == 'd' &&
                (y == (m.getFieldHeight() - 1) || (f[y + 1][x] != 'X' && f[y + 1][x] != '_')))
            return 'd';
        else
            return (currentDirection == 'u') ? 'd' : 'u';
    }
}

char Clyde::newDirection_2(const Maze & m, const Pacman & p)
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
