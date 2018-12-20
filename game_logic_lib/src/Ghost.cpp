#include "Ghost.h"

Ghost::Ghost(int y, int x, char currDir, char stayOn,
                char name, int exitCntr, int defExitCntr)
     : MazeHabitant(y, x, currDir), stayOn(stayOn), name(name),
        exitCounter(exitCntr), defaultExitCounter(defExitCntr)
{}

char Ghost::getStayOn() const { return stayOn; }
void Ghost::setStayOn(char c) { stayOn = c; }


char Ghost::makeCurrDirStep(Maze & m)
{
    int yCurr{0};
    int xCurr{0};
    if (currentDirection == 'l') { --xCurr; }
    else if (currentDirection == 'r') { ++xCurr; }
    else if (currentDirection == 'u') { --yCurr; }
    else if (currentDirection == 'd') { ++yCurr; }
    return move(m, y + yCurr, x + xCurr);
}

char Ghost::move(Maze & m, int y, int x)
{
    char ** field = m.getField();
    if (y < 0) { y = m.getFieldHeight() - 1; }
    if (y >= m.getFieldHeight()) { y = 0; }
    if (x < 0) { x = m.getFieldWidth() - 1; }
    if (x >= m.getFieldWidth()) { x = 0; }
    if (field[y][x] == 'X' || field[y][x] == '_')
        return 'N';

    if (stayOn != 'B' && stayOn != 'S' && stayOn != 'I' &&
        stayOn != 'C' && stayOn != 'P')
    {
        // this is (not crutch) for correct ghosts overlaying
        field[this->y][this->x] = stayOn;
    }
    stayOn = field[y][x];
    field[y][x] = name;
    this->y = y;
    this->x = x;
    return stayOn;
}

char Ghost::checkExitCounter(Maze & m)
{
    if (exitCounter > 0)
    {
        --exitCounter;
        return 'N';
    }
    else if (exitCounter == 0)
    {
        --exitCounter;
        return move(m, m.getGhostStart().first, m.getGhostStart().second);
    }
    else
    {
        return 'N';
    }
}

void Ghost::restoreExitCounter()
{
    exitCounter = defaultExitCounter;
}
