#include "Maze.h"

#include <iostream>
#include <ncurses.h>

Maze::Maze(MazeHabitant & pacman) : field_h(23), field_w(23)
{
    char temp[][field_w] = {
        {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
        {'X','.','.','.','.','.','.','.','.','.','.','X','.','.','.','.','.','.','.','.','.','.','X'},
        {'X','.','X','X','X','.','X','X','X','X','.','X','.','X','X','X','X','.','X','X','X','.','X'},
        {'X','o','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','o','X'},
        {'X','.','X','X','X','.','X','.','X','X','X','X','X','X','X','.','X','.','X','X','X','.','X'},
        {'X','.','.','.','.','.','X','.','.','.','.','X','.','.','.','.','X','.','.','.','.','.','X'},
        {'X','X','X','X','X','.','X','X','X','X','.','X','.','X','X','X','X','.','X','X','X','X','X'},
        {' ',' ',' ',' ','X','.','X',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','.','X',' ',' ',' ',' '},
        {' ',' ',' ',' ','X','.','X',' ','X','X','X','_','X','X','X',' ','X','.','X',' ',' ',' ',' '},
        {'X','X','X','X','X','.','X',' ','X',' ',' ',' ',' ',' ','X',' ','X','.','X','X','X','X','X'},
        {' ',' ',' ',' ',' ','.',' ',' ','X',' ',' ',' ',' ',' ','X',' ',' ','.',' ',' ',' ',' ',' '},
        {'X','X','X','X','X','.','X',' ','X',' ',' ',' ',' ',' ','X',' ','X','.','X','X','X','X','X'},
        {' ',' ',' ',' ','X','.','X',' ','X','X','X','X','X','X','X',' ','X','.','X',' ',' ',' ',' '},
        {' ',' ',' ',' ','X','.','X',' ',' ',' ',' ',' ',' ',' ',' ',' ','X','.','X',' ',' ',' ',' '},
        {'X','X','X','X','X','.','X',' ','X','X','X','X','X','X','X',' ','X','.','X','X','X','X','X'},
        {'X','.','.','.','.','.','.','.','.','.','.','X','.','.','.','.','.','.','.','.','.','.','X'},
        {'X','o','X','X','X','.','X','X','X','X','.','X','.','X','X','X','X','.','X','X','X','o','X'},
        {'X','.','.','.','X','.','.','.','.','.','.','P','.','.','.','.','.','.','X','.','.','.','X'},
        {'X','X','X','.','X','.','X','.','X','X','X','X','X','X','X','.','X','.','X','.','X','X','X'},
        {'X','.','.','.','.','.','X','.','.','.','.','X','.','.','.','.','X','.','.','.','.','.','X'},
        {'X','.','X','X','X','X','X','X','X','X','.','X','.','X','X','X','X','X','X','X','X','.','X'},
        {'X','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','X'},
        {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
    };
    field = new char*[field_h];
    for(int i = 0; i < field_h; ++i)
    {
        field[i] = new char[field_w];
        for(int j = 0; j < field_w; ++j)
        {
            field[i][j] = temp[i][j];
            if (field[i][j] == 'P')
            {
                pacman.setY(i);
                pacman.setX(j);
            }
        }
    }

    std::cout << "Constructor Maze" << std::endl;
}

Maze::~Maze()
{
    for(int i = 0; i < field_h; ++i)
    {
        delete [] field[i];
    }
    delete [] field;
    std::cout << "Destructor Maze" << std::endl;
}

int Maze::getFieldHeight() const
{
    return field_h;
}

int Maze::getFieldWidth() const
{
    return field_w;
}

char ** Maze::getField() const
{
    return field;
}

// char Maze::moveHabitant(MazeHabitant & h, int y, int x)
// {
//     if (field[y][x] == 'X' || field[y][x] == '_')
//         return 'N';
//     if (y < 0) { y = field_h - 1; }
//     if (y >= field_h) { y = 0; }
//     if (x < 0) { x = field_w - 1; }
//     if (x >= field_w) { x = 0; }

//     field[h.getY()][h.getX()] = ' ';
//     char old = field[y][x];
//     field[y][x] = 'P';
//     h.setY(y);
//     h.setX(x);
//     return old;
// }

// char Maze::shiftHabitant(MazeHabitant & h)
// {
//     const char nextDir = h.getNextDirection();
//     int yNext{0};
//     int xNext{0};
//     if (nextDir == 'l') { --xNext; }
//     else if (nextDir == 'r') { ++xNext; }
//     else if (nextDir == 'u') { --yNext; }
//     else if (nextDir == 'd') { ++yNext; }
//     char where = moveHabitant(h, h.getY() + yNext, h.getX() + xNext);
//     if (where != 'N')
//     {
//         h.setCurrDirection(nextDir);
//         return where;
//     }

//     const char currDir = h.getCurrDirection();
//     int yCurr{0};
//     int xCurr{0};
//     if (currDir == 'l') { --xCurr; }
//     else if (currDir == 'r') { ++xCurr; }
//     else if (currDir == 'u') { --yCurr; }
//     else if (currDir == 'd') { ++yCurr; }
//     where = moveHabitant(h, h.getY() + yCurr, h.getX() + xCurr);
//     if (where != 'N')
//     {
//         return where;
//     }

//     return 'N';
// }
