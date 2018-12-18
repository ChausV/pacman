#include "Ghost.h"

// Ghost::Ghost() : stayOn
// {}

char Ghost::getStayOn() const { return stayOn; }
void Ghost::setStayOn(char c) { stayOn = c; }

char Ghost::move(Maze & m, int y, int x)
{
    char ** field = m.getField();
    if (field[y][x] == 'X' || field[y][x] == '_')
        return 'N';
    if (y < 0) { y = m.getFieldHeight() - 1; }
    if (y >= m.getFieldHeight()) { y = 0; }
    if (x < 0) { x = m.getFieldWidth() - 1; }
    if (x >= m.getFieldWidth()) { x = 0; }

    if (stayOn != 'G' && stayOn != 'P')
    {
        // this is (not crutch) for correct ghosts overlaying
        field[this->y][this->x] = stayOn;
    }
    stayOn = field[y][x];
    field[y][x] = 'G';
    this->y = y;
    this->x = x;
    return stayOn;
}

char Ghost::tryToMove(Maze & m)
{
    int yCurr{0};
    int xCurr{0};
    if (currentDirection == 'l') { --xCurr; }
    else if (currentDirection == 'r') { ++xCurr; }
    else if (currentDirection == 'u') { --yCurr; }
    else if (currentDirection == 'd') { ++yCurr; }
    return move(m, y + yCurr, x + xCurr);
}
char Ghost::moveStep(Maze & m, Pacman & p)
{
    char where = tryToMove(m);
    if (where != 'N')
    {
        return where;
    }
    currentDirection = newDirection(m, p);
    return tryToMove(m);
}

char Ghost::newDirection(const Maze & m, const Pacman & p)
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
