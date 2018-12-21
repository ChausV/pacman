#ifndef GHOST_H
#define GHOST_H

#include "MazeHabitant.h"
#include "Pacman.h"

class Ghost : public MazeHabitant
{
public:
    Ghost(int y, int x, char currDir,
    		char stayOn, char name, int exitCntr, int defExitCntr,
    		int scareCnt = 0);

    char getStayOn() const;
    void setStayOn(char c);

    int	getScareCount() const;
    void setScareCount(int sc);

    virtual char move(Maze & m, int y, int x);
    virtual char moveStep(Maze & m, Pacman & p) = 0;

    void oppositeDirection();

    void restoreExitCounter();

protected:
    char stayOn;
    char name;

    int exitCounter;
    int defaultExitCounter;

    bool scareMode;
    int scareCounter;

    virtual char newDirection(const Maze & m, const Pacman & p) = 0;

    char makeCurrDirStep(Maze & m);

    char checkExitCounter(Maze & m);

    char scareDirection(const Maze & m);

};

#endif // GHOST_H
