#include "AGhost.h"
#include <random>

AGhost::AGhost(int y, int x, char currDir, char stayOn,
                char name, int exitCntr, int defExitCntr,
                int scareCnt)
     : AMazeHabitant(y, x, currDir), stayOn(stayOn), name(name),
        exitCounter(exitCntr), defaultExitCounter(defExitCntr),
        scareCounter(scareCnt)
{}

char AGhost::getStayOn() const { return stayOn; }
void AGhost::setStayOn(char c) { stayOn = c; }
int AGhost::getScareCount() const { return scareCounter; }
void AGhost::setScareCount(int sc) { scareCounter = sc; }


char AGhost::makeCurrDirStep(Maze & m)
{
    int yCurr{0};
    int xCurr{0};
    if (currentDirection == 'l') { --xCurr; }
    else if (currentDirection == 'r') { ++xCurr; }
    else if (currentDirection == 'u') { --yCurr; }
    else if (currentDirection == 'd') { ++yCurr; }
    return move(m, y + yCurr, x + xCurr);
}

char AGhost::move(Maze & m, int y, int x)
{
    char ** field = m.getField();
    if (y < 0) { y = m.getFieldHeight() - 1; }
    if (y >= m.getFieldHeight()) { y = 0; }
    if (x < 0) { x = m.getFieldWidth() - 1; }
    if (x >= m.getFieldWidth()) { x = 0; }
    if (field[y][x] == 'X' || field[y][x] == '_')
        return 'N';

    if (stayOn != 'B' && stayOn != 'S' && stayOn != 'I' &&
        stayOn != 'C' && stayOn != 'P' && stayOn != 'G')
    {
        // this is (not crutch) for correct ghosts overlaying
        field[this->y][this->x] = stayOn;
    }
    stayOn = field[y][x];
    if (scareCounter)
        field[y][x] = 'G';
    else
        field[y][x] = name;
    this->y = y;
    this->x = x;
    return stayOn;
}

char AGhost::checkExitCounter(Maze & m)
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
    
void AGhost::oppositeDirection()
{
    if (currentDirection == 'l')
        currentDirection = 'r';
    else if (currentDirection == 'r')
        currentDirection = 'l';
    else if (currentDirection == 'u')
        currentDirection = 'd';
    else if (currentDirection == 'd')
        currentDirection = 'u';
}

void AGhost::restoreExitCounter()
{
    exitCounter = defaultExitCounter;
}

char AGhost::scareDirection(const Maze & m)
{
    char ** f = m.getField();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 9);

    if (currentDirection == 'l' || currentDirection == 'r')
    {
        if (dis(gen) < 4 && f[y - 1][x] != 'X' && f[y - 1][x] != '_')
            return 'u';
        else if (dis(gen) > 4 && f[y + 1][x] != 'X' && f[y + 1][x] != '_')
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
        if (dis(gen) < 4 && f[y][x - 1] != 'X' && f[y][x - 1] != '_')
            return 'l';
        else if (dis(gen) > 4 && f[y][x + 1] != 'X' && f[y][x + 1] != '_')
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
