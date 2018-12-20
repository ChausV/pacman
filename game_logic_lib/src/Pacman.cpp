#include "Pacman.h"

char Pacman::getNextDirection() const { return nextDirection; }
void Pacman::setNextDirection(char c) { nextDirection = c; }

Pacman::Pacman(int y, int x, char currDir, char nextDir)
     : MazeHabitant(y, x, currDir), nextDirection(nextDir)
{}

char Pacman::move(Maze & m, int y, int x)
{
    char ** field = m.getField();
    if (y < 0) { y = m.getFieldHeight() - 1; }
    if (y >= m.getFieldHeight()) { y = 0; }
    if (x < 0) { x = m.getFieldWidth() - 1; }
    if (x >= m.getFieldWidth()) { x = 0; }
    if (field[y][x] == 'X' || field[y][x] == '_')
        return 'N';

    field[this->y][this->x] = ' ';
    char old = field[y][x];
    field[y][x] = 'P';
    this->y = y;
    this->x = x;
    return old;
}

char Pacman::moveStep(Maze & m)
{
    int yNext{0};
    int xNext{0};
    if (nextDirection == 'l') { --xNext; }
    else if (nextDirection == 'r') { ++xNext; }
    else if (nextDirection == 'u') { --yNext; }
    else if (nextDirection == 'd') { ++yNext; }
    char where = move(m, y + yNext, x + xNext);
    if (where != 'N')
    {
        currentDirection = nextDirection;
        return where;
    }

    int yCurr{0};
    int xCurr{0};
    if (currentDirection == 'l') { --xCurr; }
    else if (currentDirection == 'r') { ++xCurr; }
    else if (currentDirection == 'u') { --yCurr; }
    else if (currentDirection == 'd') { ++yCurr; }
    where = move(m, y + yCurr, x + xCurr);
    if (where != 'N')
    {
        return where;
    }

    return 'N';
}